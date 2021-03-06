#include <small_header.h>
#include "Game/Objects/Special/CameraZone.h"

#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/Special/ZoneTrigger.h"
#include "Game/Tools/Camera.h"
#include "Game/Tools/Recycler.h"

#include "Game/Level/Level.h"

namespace CloudberryKingdom
{

	CameraZone::ZoneTriggerLambda::ZoneTriggerLambda( const boost::shared_ptr<CameraZone> &zt )
	{
		this->zt = zt;
	}

	void CameraZone::ZoneTriggerLambda::Apply( const boost::shared_ptr<ZoneTrigger> &trig )
	{
		boost::shared_ptr<CameraZone> CamZone = boost::dynamic_pointer_cast<CameraZone>( trig );

		boost::shared_ptr<Camera> cam = CamZone->getCore()->MyLevel->getMainCamera();
		if ( cam->ZoneLocked || cam->MyPhsxType == Camera_PhsxType_FIXED )
			return;

		if ( cam->MyZone == 0 || !cam->MyZone->Activated || cam->MyZone->Priority < CamZone->Priority )
		{
			switch ( zt->CameraType )
			{
				case Camera_PhsxType_CENTER:
					if ( cam->MyPhsxType != zt->CameraType )
						cam->Target = zt->getCore()->Data.Position;
					break;
			}

			CamZone->Activated = true;

			if ( cam->MyZone == 0 )
				CamZone->SnapNext = true;

			if ( zt->SetCameraSpeed )
				cam->Speed = zt->CameraSpeed;

			cam->MyPhsxType = zt->CameraType;

			cam->MyZone = CamZone;
		}
	}

	void CameraZone::MakeNew()
	{
		ZoneTrigger::MakeNew();

		Zoom = 1;
		FreeY_MaxY = 1100;
		FreeY_MinY = -1100;

		CameraSpeed = 15;
		SetCameraSpeed = true;

		CameraType = Camera_PhsxType_SIDE_LEVEL_RIGHT;

		getCore()->MyType = ObjectType_CAMERA_ZONE;
		getCore()->GenData.Used = true;

		getCore()->ResetOnlyOnReset = true;

		Activated = false;

		Priority = 0;
	}

	CameraZone::CameraZone() :
		Zoom( 0 ), FreeY( false ), SnapNext( 0 )
	{
		MakeNew();
	}

	void CameraZone::Init( Vector2 center, Vector2 size )
	{
		ZoneTrigger::Init( center, size );

		MyContainsEvent = boost::make_shared<ZoneTriggerLambda>( boost::static_pointer_cast<CameraZone>( shared_from_this() ) );
	}

	void CameraZone::PhsxStep()
	{
		  ZoneTrigger::PhsxStep();
	}

	void CameraZone::PhsxStep2()
	{
		ZoneTrigger::PhsxStep2();

		Activated = false;
	}

	Vector2 CameraZone::GetProjectedPos( Vector2 x )
	{
		Vector2 pos = x;

		Vector2 Tangent = End - Start;
		float Length = Tangent.Length();

		float d;
		if ( Length < 1 )
		{
			d = 0;
			Length = 1;
		}
		else
		{
			d = Vector2::Dot( pos - Start, Tangent ) / Length;
		}

		return Vector2( d, 0 );
	}

	Vector2 CameraZone::FromProjected( Vector2 x )
	{
		Vector2 Tangent = End - Start;
		float Length = Tangent.Length();

		return Start + x.X * Tangent / Length;
	}

	void CameraZone::SetZoom( const boost::shared_ptr<Camera> &cam )
	{
		cam->setZoom( Zoom * Vector2( .001f,.001f ) );
	}

	void CameraZone::Enforce( const boost::shared_ptr<Camera> &cam )
	{
		SetZoom( cam );

		Vector2 pos = cam->Target;

		Vector2 Tangent = End - Start;
		float Length = Tangent.Length();

		float d;
		if ( Length < 1 )
		{
			d = 0;
			Length = 1;
		}
		else
		{
			d = Vector2::Dot( pos - Start, Tangent ) / Length;
			d = __max( 0, __min( Length, d ) );
		}

		pos = Start + d * ( End - Start ) / Length;

		if ( !FreeY )
			cam->Target = pos;
		else
		{
			cam->Target.X = pos.X;
			cam->Target.Y = __max( pos.Y + FreeY_MinY + cam->GetHeight() / 2, cam->Target.Y );
			cam->Target.Y = __min( pos.Y + FreeY_MaxY - cam->GetHeight() / 2, cam->Target.Y );
			//if (cam.Target.Y - cam.GetHeight() / 2 < pos.Y - 1000)
			  //  cam.Target.Y = pos.Y - 1000 + cam.GetHeight() / 2;
		}

		if ( SnapNext )
		{
			cam->Data.Position = cam->Target;
			SnapNext = false;
		}
	}

	void CameraZone::Move( Vector2 shift )
	{
		ZoneTrigger::Move( shift );

		Start += shift;
		End += shift;
	}

	void CameraZone::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		ZoneTrigger::Clone( A );

		boost::shared_ptr<CameraZone> ZoneA = boost::dynamic_pointer_cast<CameraZone>( A );

		Start = ZoneA->Start;
		End = ZoneA->End;

		Activated = ZoneA->Activated;

		Priority = ZoneA->Priority;

		FreeY = ZoneA->FreeY;
	}
}
