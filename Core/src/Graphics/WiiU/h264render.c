/*---------------------------------------------------------------------------*

  Copyright 2010-2011 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////
//
// h264render.c
//
// Playback AVC elementary video streams
//
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>    //for sprintf
#include <cafe/demo.h>
#include <cafe/h264.h>

#include "h264render.h"

// --------- GX2 Data ---------

GX2Texture      g_LTexture[NUM_DECODE][NUM_H264_BUFFER];
GX2Texture      g_UVTexture[NUM_DECODE][NUM_H264_BUFFER];

u32             g_H264WriteBufIdx[NUM_DECODE] = {0, 0};

// Shader data
static DEMOGfxShader s_Shader;

#if 1
static DEMO_F32x3F32x2 QUAD_VERTEX_DATA[] = {
    {-1.0f, 1.0f, 0.0f, 0.0f,  0.0f},
    { 1.0f, 1.0f, 0.0f, 1.0f,  0.0f},
    {-1.0f,-1.0f, 0.0f, 0.0f,  1.0f},
    { 1.0f,-1.0f, 0.0f, 1.0f,  1.0f},
};
#else
static DEMO_F32x3F32x2 QUAD_VERTEX_DATA[] = {
    {-0.9f, 0.9f, 0.0f, 0.0f,  0.0f},
    { 0.9f, 0.9f, 0.0f, 1.0f,  0.0f},
    {-0.9f,-0.9f, 0.0f, 0.0f,  1.0f},
    { 0.9f,-0.9f, 0.0f, 1.0f,  1.0f},
};
#endif

#define POS_OFFSET 0
#define TEXCOORD_OFFSET (sizeof(DEMO_F32x3))

// Attrib buffers for Cube
static AttribBuffer g_QuadAttribData;
static GX2Sampler g_Sampler;

static char *GSHFileName = "assets/shaders/demo_gx2/cafe/simple/nv12decode.gsh";
// Uniform inputs
static s32 g_Mode[4] = {0, 0, 0, 0};

// The initialization function for the rendering portions of this sample.
// It is responsible for allocating the three types of shaders and buffers
// as well as ensuring that data is flushed from the CPU to GPU memory
// for Shader
void InitShader()
{
    u32 attribBuffer = 0;
    void * pGshBuf;
    u32 len;

    DEMOGfxShader* pShader = &s_Shader;
    char *fileName = GSHFileName;

    // Load shader binary to memory allocated by DEMOFSSimpleRead. This
    // memory must be freed with a call to DEMOFree after shaders are loaded.
    pGshBuf = DEMOFSSimpleRead(fileName, &len);
    ASSERT(NULL != pGshBuf && "Unable to load the shader file");

    // Load shaders from memory.
    DEMOGfxLoadShaders(pShader, 0, pGshBuf);

    // Free memory allocated by DEMOFSSimpleRead when loading the shader file.
    DEMOFree(pGshBuf);

    // Init attribute to shader
    DEMOGfxInitShaderAttribute(pShader,
                               "a_position",
                               attribBuffer,
                               POS_OFFSET,
                               GX2_ATTRIB_FORMAT_32_32_32_FLOAT);

    // Init attribute to shader
    DEMOGfxInitShaderAttribute(pShader,
                               "a_texcoord",
                               attribBuffer,
                               TEXCOORD_OFFSET,
                               GX2_ATTRIB_FORMAT_32_32_FLOAT);

    // Get uniform location
    DEMOGfxGetPixelShaderUniformLocation(pShader, "u_FetchType");

    // Get sampler location
    DEMOGfxGetPixelShaderSamplerLocation(pShader, "s_Ltexture");
    DEMOGfxGetPixelShaderSamplerLocation(pShader, "s_UVtexture");

    // Initialize fetch Shader
    DEMOGfxInitFetchShader(pShader);

    // Should call for mips
    GX2InitSampler(&g_Sampler,
                   GX2_TEX_CLAMP_CLAMP,
                   GX2_TEX_XY_FILTER_BILINEAR);

    GX2InitSamplerZMFilter(&g_Sampler,
                           GX2_TEX_Z_FILTER_POINT,
                           GX2_TEX_MIP_FILTER_POINT);

}

// The Free function for ajacency shader
void FreeShader()
{
    DEMOGfxFreeShaders(&s_Shader);
}

void InitVideoBuffer(u8 decIdx, u8 bufIdx, u16 width, u16 height)
{
    // Set up another linear L8 texture
    GX2InitTexture(&g_LTexture[decIdx][bufIdx],
                   width,  // width
                   height,  // height
                   1,      // depth
                   1,      // num mips
                   GX2_SURFACE_FORMAT_TC_R8_UNORM,
                   GX2_SURFACE_DIM_2D);
    g_LTexture[decIdx][bufIdx].surface.tileMode = GX2_TILE_MODE_LINEAR_ALIGNED;

    //pitch setting doesn't seem to have any affect
    //Ltex.surface.pitch    = UVD_ALIGN_PITCH_IN_PIXELS(BITSTREAM_HEIGHT);
    // Recalculate, reinit due to tileMode change
    GX2CalcSurfaceSizeAndAlignment(&g_LTexture[decIdx][bufIdx].surface);
    GX2InitTextureRegs(&g_LTexture[decIdx][bufIdx]);

    // Set up another linear UV8 texture
    GX2InitTexture(&g_UVTexture[decIdx][bufIdx],
                   width/2,  // width
                   height/2,  // height
                   1,      // depth
                   1,      // num mips
                   GX2_SURFACE_FORMAT_TC_R8_G8_UNORM,
                   GX2_SURFACE_DIM_2D);
    g_UVTexture[decIdx][bufIdx].surface.tileMode = GX2_TILE_MODE_LINEAR_ALIGNED;

    //pitch setting doesn't seem to have any affect
    //UVtex.surface.pitch    = UVD_ALIGN_PITCH_IN_PIXELS(BITSTREAM_HEIGHT);
    // Recalculate, reinit due to tileMode change
    GX2CalcSurfaceSizeAndAlignment(&g_UVTexture[decIdx][bufIdx].surface);
    GX2InitTextureRegs(&g_UVTexture[decIdx][bufIdx]);
}

// Initialize attribute buffer and data
void InitAttribData()
{
    AttribBuffer* pAttribData = &g_QuadAttribData;
    u32 vertexDataSize = sizeof(QUAD_VERTEX_DATA);
    u32 vertexDataStride = sizeof(DEMO_F32x3F32x2);
    DEMO_F32x3F32x2* vertexData = QUAD_VERTEX_DATA;

    // Set values for vertex
    pAttribData->vertexCount   = vertexDataSize/sizeof(vertexData[0]);
    pAttribData->vertexSize   = vertexDataSize;
    pAttribData->vertexStride = vertexDataStride;

    // Allocate buffers for attributes
    pAttribData->pVertexBuffer = (f32*)DEMOGfxAllocMEM2(vertexDataSize, GX2_VERTEX_BUFFER_ALIGNMENT);

    // Set attributes data
    memcpy(pAttribData->pVertexBuffer, vertexData, vertexDataSize);

    // Invalidate attribute buffers
    GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, pAttribData->pVertexBuffer, vertexDataSize);
}

// Free attibute buffers
void FreeAttribData()
{
    AttribBuffer* pAttribData = &g_QuadAttribData;

    // Free buffers for attributes
    DEMOGfxFreeMEM2(pAttribData->pVertexBuffer);
}

void drawTVFrame()
{
    u32 attribBuffer = 0;
    u8 decIdx = 0;
    u32 h264ReadBufIdx = (g_H264WriteBufIdx[decIdx] == 0)? 1 : 0;

    GX2ClearColor(&DEMOColorBuffer, 0.0f, 0.0f, 0.0f, 1.0f);
    GX2ClearDepthStencil(&DEMODepthBuffer, GX2_CLEAR_BOTH);

    // Restore state that was saved when DEMOGfxInit was called.
    DEMOGfxSetContextState();

    GX2SetColorBuffer(&DEMOColorBuffer, GX2_RENDER_TARGET_0);
    GX2SetDepthBuffer(&DEMODepthBuffer);

    // Set Attrib buffer
    GX2SetAttribBuffer(attribBuffer,
                       g_QuadAttribData.vertexSize,
                       g_QuadAttribData.vertexStride,
                       g_QuadAttribData.pVertexBuffer);

    // This call with set all shaders.
    GX2SetShaders(&s_Shader.fetchShader,
                   s_Shader.pVertexShader,
                   s_Shader.pPixelShader);

    // Invalidate texture cache
    GX2Invalidate(GX2_INVALIDATE_TEXTURE, g_LTexture[decIdx][h264ReadBufIdx].surface.imagePtr, g_LTexture[decIdx][h264ReadBufIdx].surface.imageSize);
    GX2Invalidate(GX2_INVALIDATE_TEXTURE, g_UVTexture[decIdx][h264ReadBufIdx].surface.imagePtr, g_UVTexture[decIdx][h264ReadBufIdx].surface.imageSize);

    // Set L Texture and sampler
    GX2SetPixelTexture(&g_LTexture[decIdx][h264ReadBufIdx], s_Shader.samplersPS.location[0]);
    GX2SetPixelSampler(&g_Sampler, s_Shader.samplersPS.location[0]);

    // Set UV Texture and sampler
    GX2SetPixelTexture(&g_UVTexture[decIdx][h264ReadBufIdx], s_Shader.samplersPS.location[1]);
    GX2SetPixelSampler(&g_Sampler, s_Shader.samplersPS.location[1]);

     // Set pixel shader uniform register
    GX2SetPixelUniformReg(s_Shader.uniformsPS.location[0], 4, g_Mode);

    // Draw
    GX2Draw(GX2_PRIMITIVE_TRIANGLE_STRIP, g_QuadAttribData.vertexCount);

    return;
}


void drawDRCFrame()
{
    u32 attribBuffer = 0;
    u8 decIdx = 1;
    u32 h264ReadBufIdx = (g_H264WriteBufIdx[decIdx] == 0)? 1 : 0;

   // DEMODRCBeforeRender and DEMODRCDoneRender before and after drc drawing.
    DEMODRCBeforeRender();

    // The GX2Clear family of functions end up modifying the rendering state
    // while state shadowing is disabled. When using state shadowing it is
    // therefore necessary to call GX2SetContextState with the saved context
    // state after a call to GX2ClearColor or GX2ClearDepthStencil.
    GX2ClearColor(&DEMODRCColorBuffer,  0.45, 0.3, 0.0, 1.0f);
    GX2ClearDepthStencil(&DEMODRCDepthBuffer, GX2_CLEAR_BOTH);

    // Restore state that was saved when DEMODRCInit was called.
    GX2SetContextState(DEMODRCContextState);

    // Set Attrib buffer
    GX2SetAttribBuffer(attribBuffer,
                       g_QuadAttribData.vertexSize,
                       g_QuadAttribData.vertexStride,
                       g_QuadAttribData.pVertexBuffer);

    // This call with set all shaders.
    GX2SetShaders(&s_Shader.fetchShader,
                   s_Shader.pVertexShader,
                   s_Shader.pPixelShader);

    // Set L Texture and sampler
    GX2SetPixelTexture(&g_LTexture[decIdx][h264ReadBufIdx], s_Shader.samplersPS.location[0]);
    GX2SetPixelSampler(&g_Sampler, s_Shader.samplersPS.location[0]);

    // Set UV Texture and sampler
    GX2SetPixelTexture(&g_UVTexture[decIdx][h264ReadBufIdx], s_Shader.samplersPS.location[1]);
    GX2SetPixelSampler(&g_Sampler, s_Shader.samplersPS.location[1]);

     // Set pixel shader uniform register
    GX2SetPixelUniformReg(s_Shader.uniformsPS.location[0], 4, g_Mode);

    // Draw
    GX2Draw(GX2_PRIMITIVE_TRIANGLE_STRIP, g_QuadAttribData.vertexCount);

    // This function will copy presenting the rendered buffer to the drc screen buffer
    // Need to call DEMOGfxDoneRender for swapping after this.
    DEMODRCDoneRender();

    return;
}

