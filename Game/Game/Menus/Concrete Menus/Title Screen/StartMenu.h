#ifndef STARTMENU
#define STARTMENU

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
//#include "Core/Tools/ColorHelper.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Games/ScreenSaver.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharSelectManager.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/ControlScreen.h"
//#include "Game/Menus/Concrete Menus/Score Screens/StatsScreen.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Sub Menus/VerifyQuitGame.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Sub Menus/SoundMenu.h"
//#include "Game/Player/Stats.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct StartMenu : public CkBaseMenu
	{

		virtual ~StartMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "StartMenu" );
#endif
		}


		using CkBaseMenu::SlideOut;
		using CkBaseMenu::SlideIn;
		using CkBaseMenu::Call;
		using CkBaseMenu::Hide;

		enum Next
		{
			Next_CAMPAIGN,
			Next_ARCADE,
			Next_FREEPLAY
		};
	
		struct StartMenuLambda_Campaign : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<StartMenu> sm;
		
			StartMenuLambda_Campaign( const boost::shared_ptr<StartMenu> &sm );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct StartMenuLambda_Arcade : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<StartMenu> sm;
		
			StartMenuLambda_Arcade( const boost::shared_ptr<StartMenu> &sm );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct StartMenuLambda_Freeplay : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<StartMenu> sm;
		
			StartMenuLambda_Freeplay( const boost::shared_ptr<StartMenu> &sm );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct CharacterSelectProxy : public Lambda
		{
		
			boost::shared_ptr<StartMenu> startMenu;

		
			CharacterSelectProxy( const boost::shared_ptr<StartMenu> &startMenu );

			void Apply();
		};

	
		struct MenuGo_ScreenSaverHelper : public Lambda
		{
		
			boost::shared_ptr<StartMenu> sm;

		
			MenuGo_ScreenSaverHelper( const boost::shared_ptr<StartMenu> &sm );

			void Apply();
		};

	
		struct StartMenuLambda_Controls : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<StartMenu> sm;
		
			StartMenuLambda_Controls( const boost::shared_ptr<StartMenu> &sm );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct StartMenuLambda_Options : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<StartMenu> sm;
		
			StartMenuLambda_Options( const boost::shared_ptr<StartMenu> &sm );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct StartMenuLambda_Exit : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<StartMenu> sm;
		
			StartMenuLambda_Exit( const boost::shared_ptr<StartMenu> &sm );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct StartMenuExitLambda : public LambdaFunc_1<boost::shared_ptr<Menu> , bool>
		{
		
			boost::shared_ptr<StartMenu> sm;
		
			StartMenuExitLambda( const boost::shared_ptr<StartMenu> &sm );

			bool Apply( const boost::shared_ptr<Menu> &menu );
		};

	
		struct DoneWithCharSelectProxy : public Lambda
		{
		
			boost::shared_ptr<StartMenu> sm;

		
			DoneWithCharSelectProxy( const boost::shared_ptr<StartMenu> &sm );

			void Apply();
		};

	
		struct BringNextMenuLambda : public Lambda
		{
		
			boost::shared_ptr<StartMenu> sm;

		
			BringNextMenuLambda( const boost::shared_ptr<StartMenu> &sm );

			void Apply();
		};

	
		virtual void Hide( PresetPos pos, int frames );

		Next MyNextMenu;

	
		virtual void MenuGo_Campaign( const boost::shared_ptr<MenuItem> &item );

		virtual void MenuGo_Arcade( const boost::shared_ptr<MenuItem> &item );

		virtual void MenuGo_Freeplay( const boost::shared_ptr<MenuItem> &item );

		/// <summary>
		/// When true the user can not selected back.
		/// </summary>
		bool NoBack;

		virtual void BringCharacterSelect();

	
		virtual void Show();

		virtual void ReturnToCaller();

	
		virtual void CharacterSelect();

		virtual void MenuGo_ScreenSaver( const boost::shared_ptr<MenuItem> &item );

		virtual void MenuGo_Controls( const boost::shared_ptr<MenuItem> &item );

		virtual void MenuGo_Stats( const boost::shared_ptr<MenuItem> &item );

		virtual void MenuGo_Options( const boost::shared_ptr<MenuItem> &item );

		virtual void MenuGo_Exit( const boost::shared_ptr<MenuItem> &item );

		virtual void Exit();

	
		StartMenu();
		boost::shared_ptr<StartMenu> StartMenu_Construct();

		///// <summary>
		///// When true the menu slides in, rather than bubbles in, when a child menu returns control to it
		///// </summary>
		//bool SlideOnReturn = false;

		virtual void SlideIn( int Frames );

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		static void SetText_Green( const boost::shared_ptr<EzText> &text, bool outline );

		static void SetSelectedText_Green( const boost::shared_ptr<EzText> &text, bool outline );

		static void SetItemProperties_Green( const boost::shared_ptr<MenuItem> &item, bool outline );

		static void SetItemProperties_Red( const boost::shared_ptr<MenuItem> &item );
		static void SetTextSelected_Red( const boost::shared_ptr<EzText> &text );
		static void SetTextUnselected_Red( const boost::shared_ptr<EzText> &text );

		virtual void OnAdd();

		virtual void Init();

	
		static void GrayItem( const boost::shared_ptr<MenuItem> &item );

		virtual void MakeMenu();
	
		virtual void SetChildControl( const boost::shared_ptr<GUI_Panel> &child );

		virtual void MyPhsxStep();

	
		void DoneWithCharSelect();

	
		virtual void BringNextMenu();

	
		virtual void BringCampaign();

		virtual void BringArcade();

		virtual void BringFreeplay();

	
		virtual void OnReturnTo();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef STARTMENU
