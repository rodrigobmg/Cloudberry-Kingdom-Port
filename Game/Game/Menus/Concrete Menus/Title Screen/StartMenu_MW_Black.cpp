#include <small_header.h>
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Black.h"

#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Menus/CkBaseMenu.h"


namespace CloudberryKingdom
{

	void StartMenu_MW_Black::SlideIn( int Frames )
	{
		CkBaseMenu::SlideIn( 0 );
	}

	void StartMenu_MW_Black::SlideOut( PresetPos Preset, int Frames )
	{
		CkBaseMenu::SlideOut( Preset, 0 );
	}

	void StartMenu_MW_Black::OnAdd()
	{
		CkBaseMenu::OnAdd();
	}

	StartMenu_MW_Black::StartMenu_MW_Black() : CkBaseMenu() { }
	boost::shared_ptr<StartMenu_MW_Black> StartMenu_MW_Black::StartMenu_MW_Black_Construct()
	{
		CkBaseMenu::CkBaseMenu_Construct();

		getCore()->DrawLayer++;

		return boost::static_pointer_cast<StartMenu_MW_Black>( shared_from_this() );
	}

	void StartMenu_MW_Black::Init()
	{
		 CkBaseMenu::Init();

		MyPile = boost::make_shared<DrawPile>();

		EnsureFancy();

		//Black = new QuadClass("BlackSwipe");
		Black = boost::make_shared<QuadClass>( std::wstring( L"BlackSwipe_Vertical" ) );
		Black->ScaleXToMatchRatio( 1000 );
		Black->setSizeX( Black->getSizeX() * 1.35f );
		MyPile->Add( Black, std::wstring( L"Black" ) );

		MyPile->setAlpha( 0 );

		BlackBox();
	}

	void StartMenu_MW_Black::BlackBox()
	{

	}

	void StartMenu_MW_Black::SlideFromRight()
	{
		MyPile->setAlpha( 1 );

		float scale = 1.3f;
		Black->setSizeX( 4700 * scale );
		Black->setPos( Vector2( 9500 * scale, 0 ) );
		Black->FancyPos->LerpTo( Vector2( -6500 * scale, 0 ), 50 );
	}

	void StartMenu_MW_Black::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();
	}

	void StartMenu_MW_Black::OnReturnTo()
	{
		CkBaseMenu::OnReturnTo();
	}
}
