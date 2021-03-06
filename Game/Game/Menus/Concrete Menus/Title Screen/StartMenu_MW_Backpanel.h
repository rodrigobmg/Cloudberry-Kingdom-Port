#ifndef STARTMENU_MW_BACKPANEL
#define STARTMENU_MW_BACKPANEL

#include <small_header.h>

//#include "Core/FancyVector2.h"
//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
//#include "Core/Tools/ColorHelper.h"
//#include "Core/Tools/CoreMath.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Tools/Resources.h"


namespace CloudberryKingdom
{
	
	struct StartMenu_MW_Backpanel : public CkBaseMenu
	{

		virtual ~StartMenu_MW_Backpanel()
		{
#ifdef BOOST_BIN
			OnDestructor( "StartMenu_MW_Backpanel" );
#endif
		}


		using CkBaseMenu::SlideOut;
		using CkBaseMenu::SlideIn;
		using CkBaseMenu::Call;

		enum State
		{
			State_NONE,
							State_SCENE_TITLE,
							State_SCENE,
							State_SCENE_BLUR,
							State_SCENE_PRINCESS,
							State_SCENE_NO_BOB_BRIGHTEN,
							State_SCENE_BLUR_DARK,
							State_SCENE_KOBBLER,
							State_SCENE_KOBBLER_BLUR
		};
	
		virtual void Hide( PresetPos pos, int frames );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( PresetPos Preset, int Frames );

		virtual void OnAdd();

		void InitialZoomIn();

	
		boost::shared_ptr<QuadClass> Scene, Title, TM, Title_Trim, Scene_NoBob_Blur, Scene_Blur, Scene_Princess, Scene_NoBob_Brighten, Scene_Kobbler, Scene_Kobbler_Blur;
	
		virtual void Init();

		void SetState( State state );
	
		State MyState;

		void BlackBox();

	
		virtual void MyPhsxStep();

	
		float t;
	
		virtual void MyDraw();

	
		virtual void OnReturnTo();

	
		void InitializeInstanceFields();


		StartMenu_MW_Backpanel();
		boost::shared_ptr<StartMenu_MW_Backpanel> StartMenu_MW_Backpanel_Construct();
	};
}


#endif	//#ifndef STARTMENU_MW_BACKPANEL
