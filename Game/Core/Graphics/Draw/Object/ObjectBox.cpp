#include <small_header.h>
#include "Core/Graphics/Draw/Object/ObjectBox.h"

#include "Core/Graphics/QuadDrawer.h"
#include "Core/Graphics/Draw/Object/ObjectClass.h"
#include "Core/Graphics/Draw/Quads/ObjectVector.h"


namespace CloudberryKingdom
{

	void ObjectBox::Release()
	{
		BL->Release();
		BL.reset();
		TR->Release();
		TR.reset();
	}

	void ObjectBox::SetHold()
	{
		BL->AnimData.Hold = BL->RelPos;
		TR->AnimData.Hold = TR->RelPos;
	}

	void ObjectBox::ReadAnim( int anim, int frame )
	{
		BL->RelPos = BL->AnimData.Get( anim, frame );
		TR->RelPos = TR->AnimData.Get( anim, frame );
	}

	void ObjectBox::Record( int anim, int frame, bool UseRelativeCoords )
	{
		if ( UseRelativeCoords )
		{
			BL->AnimData.Set( BL->RelPos, anim, frame );
			TR->AnimData.Set( TR->RelPos, anim, frame );
		}
		else
		{
			BL->AnimData.Set( BL->Pos, anim, frame );
			TR->AnimData.Set( TR->Pos, anim, frame );
		}
	}

	void ObjectBox::Transfer( int anim, float DestT, int AnimLength, bool Loop, bool Linear, float t )
	{
		BL->RelPos = BL->AnimData.Transfer( anim, DestT, AnimLength, Loop, Linear, t );
		TR->RelPos = TR->AnimData.Transfer( anim, DestT, AnimLength, Loop, Linear, t );
	}

	void ObjectBox::Calc( int anim, float t, int AnimLength, bool Loop, bool Linear )
	{
		BL->RelPos = BL->AnimData.Calc( anim, t, AnimLength, Loop, Linear );
		TR->RelPos = TR->AnimData.Calc( anim, t, AnimLength, Loop, Linear );
	}

	void ObjectBox::Write( const boost::shared_ptr<BinaryWriter> &writer, const boost::shared_ptr<ObjectClass> &MainObject )
	{
		BL->Write( writer, MainObject );
		TR->Write( writer, MainObject );

		// Version 53 4/1/2010
		// Write quad name
		// Write show bool
		writer->Write( Name );
		writer->Write( Show );
	}

	void ObjectBox::Read( const boost::shared_ptr<BinaryReader> &reader, const boost::shared_ptr<ObjectClass> &MainObject, int VersionNumber )
	{
		BL->Read( reader, MainObject );
		TR->Read( reader, MainObject );

		// Version 53, 4/1/2010
		// Read name
		// Read show bool
		if ( VersionNumber > 52 )
		{
			Name = reader->ReadString();
			Show = reader->ReadBoolean();
		}
	}

	ObjectBox::ObjectBox( const boost::shared_ptr<ObjectBox> &box, bool DeepClone )
	{
		InitializeInstanceFields();
		BL = boost::make_shared<ObjectVector>();
		BL->ModifiedEventCallback = boost::make_shared<ObjectVector::DefaultCallbackLambda>( BL->shared_from_this() );
		box->BL->Clone( BL, DeepClone );
		TR = boost::make_shared<ObjectVector>();
		TR->ModifiedEventCallback = boost::make_shared<ObjectVector::DefaultCallbackLambda>( TR->shared_from_this() );
		box->TR->Clone( TR, DeepClone );

		Show = box->Show;
		Name = box->Name;
	}

	ObjectBox::ObjectBox()
	{
		InitializeInstanceFields();
		BL = boost::make_shared<ObjectVector>();
		BL->ModifiedEventCallback = boost::make_shared<ObjectVector::DefaultCallbackLambda>( BL->shared_from_this() );
		TR = boost::make_shared<ObjectVector>();
		TR->ModifiedEventCallback = boost::make_shared<ObjectVector::DefaultCallbackLambda>( TR->shared_from_this() );

		Name = std::wstring( L"Box" );
	}

	void ObjectBox::Update()
	{
		BL->PosFromRelPos();
		TR->PosFromRelPos();
	}

	Vector2 ObjectBox::Center()
	{
		return ( TR->Pos + BL->Pos ) / 2;
	}

	Vector2 ObjectBox::Size()
	{
		return ( TR->Pos - BL->Pos );
	}

	void ObjectBox::DrawExtra( const boost::shared_ptr<QuadDrawer> &Drawer, Color clr )
	{
		if ( !Show )
			return;

		Drawer->DrawLine( BL->Pos, Vector2( TR->Pos.X, BL->Pos.Y ), clr,.02f );
		Drawer->DrawLine( BL->Pos, Vector2( BL->Pos.X, TR->Pos.Y ), clr,.02f );
		Drawer->DrawLine( TR->Pos, Vector2( TR->Pos.X, BL->Pos.Y ), clr,.02f );
		Drawer->DrawLine( TR->Pos, Vector2( BL->Pos.X, TR->Pos.Y ), clr,.02f );
	}

	void ObjectBox::InitializeInstanceFields()
	{
		Show = true;
	}
}
