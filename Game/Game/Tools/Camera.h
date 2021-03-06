#ifndef CAMERA
#define CAMERA

#include <small_header.h>

#include "Core/FancyVector2.h"
#include "Core/PhsxData.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/Special/CameraZone.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct Camera : public IPos, public boost::enable_shared_from_this<Camera>
	{

		static void InitializeStatics();
	
		/// <summary>
		/// When true the camera uses its EffectivePos and EffectiveZoom when drawing.
		/// The camera's TR, BL, width, and height are unaffected and are updated normally.
		/// This allows the camera to be moved without affecting what is drawn.
		/// </summary>
		bool UseEffective;
		Vector2 EffectivePos;
		Vector2 EffectiveZoom;

		Vector4 VertexCam;

		bool RocketManCamera;

		boost::shared_ptr<FancyVector2> FancyPos, FancyZoom;

		bool Shaking, Oscillating;
		float ShakingIntensity;
		Vector2 ShakingSaveZoom, ShakingSavePos;

		boost::shared_ptr<CameraZone> MyZone;

		/// <summary>
		/// If true the camera will not interact with other CameraZones
		/// </summary>
		bool ZoneLocked;

		boost::shared_ptr<Level> MyLevel;
		PhsxData Data;
		Vector2 PrevPos, PrevPrevPos;

		Vector2 getPos();
		void setPos( const Vector2 &value );

		Vector2 PosToScreenPos( Vector2 pos, float parallax );


		/// <summary>
		/// The current maximum speed amonst all the alive players.
		/// </summary>
		Vector2 MaxPlayerSpeed;

		float Speed, SpeedVel, TargetSpeed;
		Vector2 Target;
	
		Vector2 _Zoom;
	
		const Vector2 &getZoom() const;
		void setZoom( const Vector2 &value );

		Vector2 getScreenSize() const;

		Vector2 Offset;
		int ScreenWidth, ScreenHeight;
		float AspectRatio;

		Vector2 TR, BL;
		Vector2 EffectiveTR, EffectiveBL;

		Vector2 BLCamBound, TRCamBound;

		bool FollowCenter;

		void Release();


		void Move( Vector2 shift );

		void Clone( const boost::shared_ptr<Camera> &cam );
		void Clone( const boost::shared_ptr<Camera> &cam, bool DataOnly );

		void MakeFancyPos();

		Vector2 GetSize();

		float GetHeight();

		float GetWidth();

	
		int LastUpdate;
	
		void Update();

		Camera();

		Camera( int width, int height );

		void Init( int width, int height );

		Camera( const boost::shared_ptr<Camera> &cam );

		Vector2 ShakeOffset, OscillateOffset;
	
		int ShakeCount, ShakeLength;
	
		void StartShake();
		void StartShake( float Intensity );
		void StartShake( float Intensity, int Length );
		void StartShake( float Intensity, int Length, bool Sound );

		void EndShake();

		bool OnScreen( Vector2 pos );
		bool OnScreen( Vector2 pos, Vector2 GraceSize );
		bool OnScreen( Vector2 pos, float GraceSize );
		bool OnScreen( Vector2 bl, Vector2 tr, float GraceSize );


	
		Vector4 GetVertex();

	
		void SetVertexCamera();

		void SetVertexZoom( float factor );
		void SetVertexZoom( Vector2 factor );

		void SetVertexCamera( Vector2 shift, Vector2 factor );

		Vector2 HoldZoom;
		void SetToDefaultZoom();

		void RevertZoom();

		Vector2 CurVel();

		static bool DisableOscillate;

		Camera_PhsxType MyPhsxType;
	
		float t;
	
		void PhsxStep();

		void SetPhsxType( Camera_PhsxType NewType );

		void Fixed_PhsxStep();

		void WorldMap_PhsxStep();

		void Center_PhsxStep();

		/// <summary>
		/// Forces the camera's Target.X to be within a given box.
		/// </summary>
		/// <param name="Pos"></param>
		/// <param name="BoxSize"></param>
		/// <param name="BoxShift"></param>
	
		Vector2 BoxLimit_X( Vector2 Pos, Vector2 BoxCenter, Vector2 BoxSize, Vector2 BoxShift );

		/// <summary>
		/// Forces the camera's Target.Y to be within a given box.
		/// </summary>
		/// <param name="Pos"></param>
		/// <param name="BoxSize"></param>
		/// <param name="BoxShift"></param>
		Vector2 BoxLimit_Y( Vector2 Pos, Vector2 BoxCenter, Vector2 BoxSize, Vector2 BoxShift );

		Vector2 BoxLimitLeft( Vector2 Pos, Vector2 BoxCenter, Vector2 BoxSize, Vector2 BoxShift );

		Vector2 BoxLimitDown( Vector2 Pos, Vector2 BoxCenter, Vector2 BoxSize, Vector2 BoxShift );
		Vector2 BoxLimitUp( Vector2 Pos, Vector2 BoxCenter, Vector2 BoxSize, Vector2 BoxShift );

	
		bool MovingCamera;
		void SideLevel_PhsxStep();

	
		void InitializeInstanceFields();
	};

}

#endif	//#ifndef CAMERA
