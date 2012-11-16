#include "GUI_Level.h"
#include "Game/Tools/Tools.h"
#include "Core/Text/EzText.h"
#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Text/EzFont.h"
#include "Game/Tools/Resources.h"
#include "Properties/Resources.Designer.h"

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	GUI_CampaignLevel::GUI_CampaignLevel() : GUI_Level(false)
	{
	}

	void GUI_CampaignLevel::OnAdd()
	{
		GUI_Level::OnAdd();

		UpdateLevelText();
	}

	std::wstring GUI_CampaignLevel::ToString()
	{
		if ( MyGame == 0 )
			return _T( "   " );

		return MyGame->MyLevel->Name;
	}

	std::wstring GUI_Level::ToString()
	{
		Tools::Warning();
		return Localization::WordString( Prefix ) + _T( " " ) + StringConverterHelper::toString( Level_Renamed );
	}

	void GUI_Level::OnAdd()
	{
		GUI_Panel::OnAdd();

		if ( !AddedOnce )
		{
			if ( DoSlideIn )
			{
				SlideOut( PresetPos_TOP, 0 );
				SlideIn();
				Show();
			}
			else
			{
				SlideIn( 0 );
				Show();
			}
		}

		AddedOnce = true;
	}

	void GUI_Level::ReleaseBody()
	{
		GUI_Panel::ReleaseBody();
	}

	void GUI_Level::SetLevel( int Level_Renamed )
	{
		if ( this->Level_Renamed != Level_Renamed )
		{
			this->Level_Renamed = Level_Renamed;
			UpdateLevelText();
		}
	}

	void GUI_Level::UpdateLevelText()
	{
		LevelText->SubstituteText( ToString() );
	}

	GUI_Level::GUI_Level()
	{
		InitializeInstanceFields();
		DoInit( false );
	}

	GUI_Level::GUI_Level( bool SlideIn )
	{
		InitializeInstanceFields();
		DoInit( SlideIn );
	}

	GUI_Level::GUI_Level( int LevelNum )
	{
		InitializeInstanceFields();
		DoInit( false );
		PreventRelease = false;

		SetLevel( LevelNum );
	}

	void GUI_Level::DoInit( bool SlideIn )
	{
		DoSlideIn = SlideIn;

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		MyPile->setPos( Vector2( 1590.556f, 803.2224f ) );

		// Object is carried over through multiple levels, so prevent it from being released.
		PreventRelease = true;

		PauseOnPause = true;

		MyPile->FancyPos->UpdateWithGame = true;


		std::shared_ptr<EzFont> font;
		float scale;
		Color c, o;

		if ( false )
		{
			font = Resources::Font_Grobold42;
			scale = .5f;
			c = Color::White;
			o = Color::Black;
		}
		else
		{
			font = Resources::Font_Grobold42;
			scale = .55f;
			c = Color( 228, 0, 69 );
			o = Color::White;
		}

		LevelText = std::make_shared<EzText>( ToString(), font, 950, false, true );
		LevelText->setScale( scale );
		LevelText->MyFloatColor = c.ToVector4();
		LevelText->OutlineColor = o.ToVector4();


		LevelText->RightJustify = true;

		MyPile->Add( LevelText );
	}

	void GUI_Level::MyDraw()
	{
		if ( !getCore()->Show || getCore()->MyLevel->SuppressCheckpoints )
			return;

		GUI_Panel::MyDraw();
	}

	void GUI_Level::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( Hid || !Active )
			return;

		if ( getCore()->MyLevel->Watching || getCore()->MyLevel->Finished )
			return;
	}

	void GUI_Level::InitializeInstanceFields()
	{
		Prefix = Localization::Words_LEVEL;
		DoSlideIn = true;
		AddedOnce = false;
	}
}