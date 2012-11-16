﻿#include "BaseQuad.h"
#include "Core/Graphics/Draw/Object/ObjectClass.h"
#include "Core/Graphics/Draw/Quads/Quad.h"
#include "Core/Graphics/VertexFormat.h"
#include "Core/Tools/ColorHelper.h"
#include "Core/Texture/EzTexture.h"
#include "Core/Effects/EzEffect.h"
#include "Core/Animation/AnimationData_Integer.h"
#include "Core/Graphics/Draw/Quads/ObjectVector.h"
#include "Core/Effects/EzEffectWad.h"
#include "Core/Texture/CloudberryKingdom.EzTextureWad.h"
#include "Core/Graphics/QuadDrawer.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Graphics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{

	const Microsoft::Xna::Framework::Matrix &BaseQuad::getMyMatrix() const
	{
		return _MyMatrix;
	}

	void BaseQuad::setMyMatrix( const Matrix &value )
	{
		_MyMatrix = value;
		MyMatrixSignature = ColorHelper::MatrixSignature( _MyMatrix );
	}

	const bool &BaseQuad::getTextureIsAnimated() const
	{
		return TextureAnim != 0 && TextureAnim->Anims.size() > 0;
	}

	bool BaseQuad::Is( const std::wstring &Name )
	{
	#if defined(XBOX)
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Compare' reference is not converted:
		return std::wstring::Compare( this->Name, Name, System::StringComparison::CurrentCultureIgnoreCase ) == 0;
	#else
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Compare' reference is not converted:
		return std::wstring::Compare( this->Name, Name, true ) == 0;
	#endif
	}

	void BaseQuad::Clone( const std::shared_ptr<BaseQuad> &quad )
	{
		Show = quad->Show;

		setMyMatrix( quad->getMyMatrix() );

		Name = quad->Name;
		MyDrawOrder = quad->MyDrawOrder;

		MyColor = quad->MyColor;
		PremultipliedColor = quad->PremultipliedColor;
		MyEffect = quad->MyEffect;
		MyTexture = quad->MyTexture;
	}

	void BaseQuad::Release()
	{
		Released = true;

		ParentObject.reset();
		ParentQuad.reset();
		Vertices.clear();
		MyTexture.reset();
		MyEffect.reset();
	}

	void BaseQuad::Update()
	{
		Update( 1 );
	}

	void BaseQuad::Update( float Expand )
	{
	}

	void BaseQuad::SetHold()
	{
	}

	void BaseQuad::ReadAnim( int anim, int frame )
	{
	}

	void BaseQuad::Record( int anim, int frame, bool UseRelativeCoords )
	{
	}

	void BaseQuad::Calc( int anim, float t, int AnimLength, bool Loop, bool Linear )
	{
	}

	void BaseQuad::Transfer( int anim, float DestT, int AnimLength, bool Loop, bool DestLinear, float t )
	{
	}

	void BaseQuad::CopyAnim( const std::shared_ptr<BaseQuad> &quad, int Anim )
	{
	}

	void BaseQuad::CopyAnimShallow( const std::shared_ptr<BaseQuad> &quad, int Anim )
	{
	}

	void BaseQuad::Write( const std::shared_ptr<BinaryWriter> &writer )
	{
		// Version 51, 3/31/2010
		// Write draw order
		// Write quad name
		writer->Write( Name );
		writer->Write( static_cast<int>( MyDrawOrder ) );

		// Version 52, 4/1/2010
		// Write show bool
		writer->Write( Show );

		// Version 52, 7/25/2012
		// Write texture anim data
		if ( TextureAnim == 0 )
			writer->Write( 0 );
		else
		{
			writer->Write( 1 );
			TextureAnim->Write( writer );
		}
	}

	void BaseQuad::Read( const std::shared_ptr<BinaryReader> &reader, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<EzTextureWad> &TextureWad, int VersionNumber )
	{
		// Version 51, 3/31/2010
		// Read in draw order
		// Read in quad name
		if ( VersionNumber > 50 )
		{
			Name = reader->ReadString();
			MyDrawOrder = static_cast<ObjectDrawOrder>( reader->ReadInt32() );
		}

		// Version 52, 4/1/2010
		// Read show bool
		if ( VersionNumber > 51 )
			Show = reader->ReadBoolean();

		// Version 54, 7/25/2012
		// Read texture anim data
		if ( VersionNumber > 53 )
		{
			int exists = reader->ReadInt32();
			if ( exists == 1 )
			{
				if ( TextureAnim == 0 )
					TextureAnim = std::make_shared<AnimationData_Texture>();
				TextureAnim->Read( reader );
			}
		}
	}

#if defined(EDITOR)
	void BaseQuad::SaveState( int StateIndex )
	{
	}
#endif

#if defined(EDITOR)
	void BaseQuad::RecoverState( int StateIndex )
	{
	}
#endif

	Microsoft::Xna::Framework::Vector2 BaseQuad::BL()
	{
		Vector2 BL = Vector2( 100000, 100000 );
		for ( int i = 0; i < NumVertices; i++ )
			BL = Vector2::Min( BL, Vertices[ i ].xy );

		return BL;
	}

	Microsoft::Xna::Framework::Vector2 BaseQuad::TR()
	{
		Vector2 TR = Vector2( -100000, -100000 );
		for ( int i = 0; i < NumVertices; i++ )
			TR = Vector2::Max( TR, Vertices[ i ].xy );

		return TR;
	}

	void BaseQuad::SetTexture( const std::wstring &Name, const std::shared_ptr<EzTextureWad> &Wad )
	{
		MyTexture = Wad->FindByName( Name );
	}

	void BaseQuad::SetEffect( const std::wstring &Name, const std::shared_ptr<EzEffectWad> &Wad )
	{
		MyEffect = Wad->FindByName( Name );
	}

	void BaseQuad::OrphanSelf()
	{
		ParentQuad->RemoveQuadChild( this );
	}

	void BaseQuad::FinishLoading( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzTextureWad> &TexWad, const std::shared_ptr<EzEffectWad> &EffectWad )
	{
		FinishLoading( device, TexWad, EffectWad, true );
	}

	void BaseQuad::FinishLoading( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzTextureWad> &TexWad, const std::shared_ptr<EzEffectWad> &EffectWad, bool UseNames )
	{
	}

	void BaseQuad::Draw()
	{
	}

	void BaseQuad::Draw( const std::shared_ptr<QuadDrawer> &QDrawer )
	{
	}

	void BaseQuad::DrawExtra( const std::shared_ptr<QuadDrawer> &QDrawer, bool Additional, float ScaleLines )
	{
	}

	bool BaseQuad::HitTest( Vector2 x )
	{
		return false;
	}

#if defined(EDITOR)
	std::vector<ObjectVector*> BaseQuad::GetObjectVectors()
	{
		return std::vector<ObjectVector*>();
	}
#endif

#if defined(EDITOR)
	void BaseQuad::ColoredDraw( const std::shared_ptr<QuadDrawer> &QDrawer, Color color )
	{
		std::vector<MyOwnVertexFormat> hold = std::vector<MyOwnVertexFormat>( Vertices.size() );
		Vertices.CopyTo( hold, 0 );

		SetColor( color );

		Draw( QDrawer );
		QDrawer->Flush();

		hold.CopyTo( Vertices, 0 );
	}
#endif

	void BaseQuad::SetColor( Color color )
	{
		MyColor = color;

		PremultipliedColor = ColorHelper::PremultiplyAlpha( color );

		for ( int i = 0; i < NumVertices; i++ )
			Vertices[ i ].Color = PremultipliedColor;
	}

	void BaseQuad::Set_PosFromRelPos( const std::shared_ptr<ObjectVector> &v )
	{
	}

	void BaseQuad::Set_RelPosFromPos( const std::shared_ptr<ObjectVector> &v )
	{
	}

#if defined(EDITOR)
	void BaseQuad::ClickOnChildButton()
	{
		SetToBeChild = !SetToBeChild;
	}
#endif

#if defined(EDITOR)
	void BaseQuad::ClickOnReleaseButton()
	{
		if ( ParentQuad != 0 && ParentQuad != ParentObject->ParentQuad )
			ParentQuad->RemoveQuadChild( this );
	}
#endif

	void BaseQuad::InitializeInstanceFields()
	{
		_MyMatrix = Matrix::Identity;
		UpdateSpriteAnim = true;
		Show = true;
#if defined(EDITOR)
		Expanded = true;
#endif
	}
}