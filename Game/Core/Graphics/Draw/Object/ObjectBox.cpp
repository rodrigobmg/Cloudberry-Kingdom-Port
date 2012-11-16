﻿#include "ObjectBox.h"
#include "Core/Graphics/Draw/Quads/ObjectVector.h"
#include "Core/Graphics/Draw/Object/ObjectClass.h"
#include "Core/Graphics/QuadDrawer.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Audio;
using namespace Microsoft::Xna::Framework::Content;
using namespace Microsoft::Xna::Framework::Graphics;
using namespace Microsoft::Xna::Framework::Input;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

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

	void ObjectBox::Write( const std::shared_ptr<BinaryWriter> &writer, const std::shared_ptr<ObjectClass> &MainObject )
	{
		BL->Write( writer, MainObject );
		TR->Write( writer, MainObject );

		// Version 53 4/1/2010
		// Write quad name
		// Write show bool
		writer->Write( Name );
		writer->Write( Show );
	}

	void ObjectBox::Read( const std::shared_ptr<BinaryReader> &reader, const std::shared_ptr<ObjectClass> &MainObject, int VersionNumber )
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

	ObjectBox::ObjectBox( const std::shared_ptr<ObjectBox> &box, bool DeepClone )
	{
		InitializeInstanceFields();
		BL = std::make_shared<ObjectVector>();
		box->BL->Clone( BL, DeepClone );
		TR = std::make_shared<ObjectVector>();
		box->TR->Clone( TR, DeepClone );

		Show = box->Show;
		Name = box->Name;
	}

	ObjectBox::ObjectBox()
	{
		InitializeInstanceFields();
		BL = std::make_shared<ObjectVector>();
		TR = std::make_shared<ObjectVector>();

		Name = _T( "Box" );
	}

	void ObjectBox::Update()
	{
		BL->PosFromRelPos();
		TR->PosFromRelPos();
	}

	Microsoft::Xna::Framework::Vector2 ObjectBox::Center()
	{
		return ( TR->Pos + BL->Pos ) / 2;
	}

	Microsoft::Xna::Framework::Vector2 ObjectBox::Size()
	{
		return ( TR->Pos - BL->Pos );
	}

#if defined(EDITOR)
	std::vector<ObjectVector*> ObjectBox::GetObjectVectors()
	{
		std::vector<ObjectVector*> ObjectVectorList = std::vector<ObjectVector*>();

		ObjectVectorList.push_back( BL );
		ObjectVectorList.push_back( TR );

		return ObjectVectorList;
	}
#endif

#if defined(EDITOR)
	void ObjectBox::SaveState( int StateIndex )
	{
		TR->SaveState( StateIndex );
		BL->SaveState( StateIndex );
	}
#endif

#if defined(EDITOR)
	void ObjectBox::RecoverState( int StateIndex )
	{
		TR->RecoverState( StateIndex );
		BL->RecoverState( StateIndex );
	}
#endif

	void ObjectBox::DrawExtra( const std::shared_ptr<QuadDrawer> &Drawer, Color clr )
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