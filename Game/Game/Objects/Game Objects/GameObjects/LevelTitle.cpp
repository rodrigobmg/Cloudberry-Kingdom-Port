#include <small_header.h>
#include "Game/Objects/Game Objects/GameObjects/LevelTitle.h"

#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Text/EzText.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Tools/Resources.h"
#include "Game/Tools/Tools.h"

#include "Game/Games/GameType.h"
#include "Game/Tools/Camera.h"
#include "Game/Level/Level.h"

namespace CloudberryKingdom
{

	void LevelTitle::OnAdd()
	{
		GUI_Panel::OnAdd();

		//Vector2 shift = new Vector2(0, -.5f * Core.MyLevel.MainCamera.GetHeight() + 380);
		Vector2 shift = Vector2( 0, -.5f * 2000 + 380 );

		// Add the text
		text->setPos( shift );
		MyPile->Add( text );

		// Scale to fit
		Vector2 size = text->GetWorldSize();
		float max = MyGame->getCam()->GetWidth() - 400;
		if ( size.X > max )
			text->setScale( text->getScale() * max / size.X );

		// Slide out
		this->SlideOut( PresetPos_BOTTOM, 0 );

		if ( Perma )
			this->SlideIn( 0 );
	}

	LevelTitle::LevelTitle( const std::wstring &str ) :
		Perma( false ),
		Count( 0 )
	{
	}
	boost::shared_ptr<LevelTitle> LevelTitle::LevelTitle_Construct( const std::wstring &str )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Init( str, Vector2(), 1, false );

		return boost::static_pointer_cast<LevelTitle>( shared_from_this() );
	}

	LevelTitle::LevelTitle( const std::wstring &str, Vector2 shift, float scale, bool perma ) :
		Perma( false ),
		Count( 0 )
	{
	}
	boost::shared_ptr<LevelTitle> LevelTitle::LevelTitle_Construct( const std::wstring &str, Vector2 shift, float scale, bool perma )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Init( str, shift, scale, perma );

		return boost::static_pointer_cast<LevelTitle>( shared_from_this() );
	}

	boost::shared_ptr<LevelTitle> LevelTitle::HeroTitle( const std::wstring &str )
	{
		boost::shared_ptr<LevelTitle> title = MakeMagic( LevelTitle, ( str, Vector2( 150.f, -130.f ), 1.f, false ) );
		title->SlideInLength = 55;

		return title;
	}

	void LevelTitle::Init( const std::wstring &str, Vector2 shift, float scale, bool perma )
	{
		SlideInLength = 84;

		this->Perma = perma;

		//Core.DrawLayer++; // Draw above cheering berries
		PauseOnPause = true;

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();
		MyPile->setPos( MyPile->getPos() + shift );

		Tools::Warning(); // May be text, rather than Localization.Words
		text = boost::make_shared<EzText>( str, Resources::Font_Grobold42, true, true );
		text->setScale( text->getScale() * scale );

		text->MyFloatColor = ( bColor( 26, 188, 241 ) ).ToVector4();
		text->OutlineColor = ( bColor( 255, 255, 255 ) ).ToVector4();

		text->Shadow = true;
		text->ShadowOffset = Vector2( 10.5f, 10.5f );
		text->ShadowColor = bColor( 30, 30, 30 );
	}

	void LevelTitle::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		Count++;

		// Make sure we're on top
		if ( !getCore()->Released && getCore()->MyLevel != 0 )
			getCore()->MyLevel->MoveToTopOfDrawLayer( shared_from_this() );

		// Do nothing if this is permanent
		if ( Perma )
			return;

		// Otherwise show and hide
		if ( Count == 4 )
			SlideIn();

		if ( Count == 180 )
		{
			SlideOut( PresetPos_BOTTOM, 160 );
			ReleaseWhenDone = true;
		}
	}

	void LevelTitle::InitializeInstanceFields()
	{
		Count = 0;
	}
}
