#ifndef CUSTOMLEVEL_GUI
#define CUSTOMLEVEL_GUI

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
//#include "Game/Tilesets/TileSet.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Games/GameType.h"
//#include "Game/Games/CampaignHelper.h"
//#include "Game/Games/NormalGame.h"
//#include "Game/Games/Meta Games/Challenges/_Regular.h"
//#include "Game/Level/Make/LockableBool.h"
//#include "Game/Level/Make/LevelSeedData.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/SaveLoadSeedMenu.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomHero_GUI.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomUpgrades_GUI.h"
//#include "Game/Menus/Menu Components/MenuSliderBase.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/LengthSlider.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/SavedSeedsGUI.h"
//#include "Game/Menus/Menu Components/MenuList.h"
//#include "Game/Menus/Menu Components/MenuSliderNoSlide.h"
//#include "Game/Objects/Icon.h"
//#include "Game/Menus/Concrete Menus/Help/HelpMenu.h"
//#include "Game/Player/Hero Physics/BobPhsxRandom.h"
//#include "Game/Player/Hero Physics/Rocketbox.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tools/WrappedFloat.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{

	struct CustomLevel_GUI : public CkBaseMenu
	{

		virtual ~CustomLevel_GUI()
		{
#ifdef BOOST_BIN
			OnDestructor( "CustomLevel_GUI" );
#endif
		}


		using CkBaseMenu::SlideOut;
		using CkBaseMenu::SlideIn;

		static void InitializeStatics();
	
		struct StartLevelFromMenDataStandardLoadProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			boost::shared_ptr<LevelSeedData> data;

		
			StartLevelFromMenDataStandardLoadProxy( const boost::shared_ptr<LevelSeedData> &data );

			void Apply( const boost::shared_ptr<Level> &level );
		};

	
		struct StartLevelFromMenuDataInitializeHelper : public Lambda_1<boost::shared_ptr<PieceSeedData> >
		{
		
			boost::shared_ptr<CustomLevel_GUI> clGui;

		
			StartLevelFromMenuDataInitializeHelper( const boost::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply( const boost::shared_ptr<PieceSeedData> &piece );
		};

	
		struct StartLevelEnableLoadProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			boost::shared_ptr<LevelSeedData> data;

		
			StartLevelEnableLoadProxy( const boost::shared_ptr<LevelSeedData> &data );

			void Apply( const boost::shared_ptr<Level> &level );
		};

	
		struct OnReturnFromLevelProxy : public Lambda
		{
		
			boost::shared_ptr<CustomLevel_GUI> clGui;

		
			OnReturnFromLevelProxy( const boost::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	
		struct InitOnSetValueHelper : public Lambda
		{
		
			boost::shared_ptr<CustomLevel_GUI> clGui;
			boost::shared_ptr<LengthSlider> length;

		
			InitOnSetValueHelper( const boost::shared_ptr<CustomLevel_GUI> &clGui, const boost::shared_ptr<LengthSlider> &length );

			void Apply();
		};

	
		struct InitOnSlideHelper : public Lambda
		{
		
			boost::shared_ptr<CustomLevel_GUI> clGui;
			boost::shared_ptr<LengthSlider> length;

		
			InitOnSlideHelper( const boost::shared_ptr<CustomLevel_GUI> &clGui, const boost::shared_ptr<LengthSlider> &length );

			void Apply();
		};

	
		struct InitOnSlideHelper2 : public Lambda
		{
		
			boost::shared_ptr<CustomLevel_GUI> clGui;
			boost::shared_ptr<LengthSlider> length;

		
			InitOnSlideHelper2( const boost::shared_ptr<CustomLevel_GUI> &clGui, const boost::shared_ptr<LengthSlider> &length );

			void Apply();
		};

	
		struct InitOnSetValueHelper2 : public Lambda
		{
		
			boost::shared_ptr<CustomLevel_GUI> clGui;
			boost::shared_ptr<LengthSlider> length;

		
			InitOnSetValueHelper2( const boost::shared_ptr<CustomLevel_GUI> &clGui, const boost::shared_ptr<LengthSlider> &length );

			void Apply();
		};

	
		struct InitOnAStartHelper : public LambdaFunc_1<boost::shared_ptr<Menu> , bool>
		{
		
			boost::shared_ptr<CustomLevel_GUI> clGui;

		
			InitOnAStartHelper( const boost::shared_ptr<CustomLevel_GUI> &clGui );

			bool Apply( const boost::shared_ptr<Menu> &dummy );
		};

	
		struct InitOnIndexSelectHelper : public Lambda
		{
		
			boost::shared_ptr<CustomLevel_GUI> clGui;
			boost::shared_ptr<MenuList> LocationList;

		
			InitOnIndexSelectHelper( const boost::shared_ptr<CustomLevel_GUI> &clGui, const boost::shared_ptr<MenuList> &LocationList );

			void Apply();
		};

	
		struct InitOnIndexSelect : public Lambda
		{
		
			boost::shared_ptr<CustomLevel_GUI> clGui;
			boost::shared_ptr<MenuList> GameList;

		
			InitOnIndexSelect( const boost::shared_ptr<CustomLevel_GUI> &clGui, const boost::shared_ptr<MenuList> &GameList );

			void Apply();
		};

	
		struct DiffList_OnIndexProxy : public Lambda
		{
		
			boost::shared_ptr<CustomLevel_GUI> clGui;

		
			DiffList_OnIndexProxy( const boost::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	
		struct HeroList_OnIndexProxy : public Lambda
		{
		
			boost::shared_ptr<CustomLevel_GUI> clGui;

		
			HeroList_OnIndexProxy( const boost::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	
		struct BringNextProxy : public Lambda
		{
		
			boost::shared_ptr<CustomLevel_GUI> clGui;

		
			BringNextProxy( const boost::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	
		struct BringLoadProxy : public Lambda
		{
		
			boost::shared_ptr<CustomLevel_GUI> clGui;

		
			BringLoadProxy( const boost::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply();
		};

	
		struct BringLoadProxy1 : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<CustomLevel_GUI> clGui;

		
			BringLoadProxy1( const boost::shared_ptr<CustomLevel_GUI> &clGui );

			void Apply( const boost::shared_ptr<MenuItem> &dummy );
		};

	
		static std::vector<boost::shared_ptr<TileSet> > FreeplayTilesets;
		static std::vector<boost::shared_ptr<BobPhsx> > FreeplayHeroes;

		static bool IsMaxLength;
		static int Difficulty;

		/// <summary>
		/// This is the level seed being edited.
		/// </summary>
		boost::shared_ptr<LevelSeedData> LevelSeed;
		boost::shared_ptr<PieceSeedData> PieceSeed;

		boost::shared_ptr<ObjectIcon> HeroIcon, MiniCheckpoint;

	
		static Localization::Words CustomHeroString;

	
		CustomLevel_GUI();
		boost::shared_ptr<CustomLevel_GUI> CustomLevel_GUI_Construct();

		void StartLevelFromMenuData();

		void StartLevel( const boost::shared_ptr<LevelSeedData> &data );

		virtual void OnAdd();

	
		virtual void ReleaseBody();

	
		void OnReturnFromLevel();

		void AnyHero();

		void UpHero_ModShown();

		void UpHero_NoSpaceship();

		void ShowHeros( bool Show );

		float HoldNumCheckpoints;
		int HoldDesiredNumCheckpoints;
		void ShowCheckpoints( bool Show );

		bool HasWall;
		void SelectNormal();

		void SelectBuild();

		void SelectBungee();

		void SelectSurvival();

		bool LeftJustify;
		float LeftJustifyAddX;

		//static Vector2 RightPanelCenter = new Vector2(-410, 75);
		static Vector2 RightPanelCenter;
		boost::shared_ptr<LengthSlider> length;
		boost::shared_ptr<MenuSliderBase> checkpoints;
		boost::shared_ptr<MenuItem> Start;
		boost::shared_ptr<MenuList> HeroList, DiffList;
		boost::shared_ptr<EzText> HeroText, CheckpointsText;
	
		virtual void Init();

	
		boost::shared_ptr<MenuItem> AddHeroItem( const boost::shared_ptr<BobPhsx> &hero );

		void DiffList_OnIndex();

		void StartLevel();

		void HeroList_OnIndex();

		bool IsCustomHero();

	
		bool IsCustomDifficulty();

		void SetPos();

	
		void SelectUpLevel();

		void SelectDownLevel();

		/// <summary>
		/// The panel that actually starts the level, when it is started.
		/// </summary>
	
		boost::shared_ptr<GUI_Panel> CallingPanel;

	
		void BringNext();

	
		virtual void Show();

	
		boost::shared_ptr<CustomHero_GUI> HeroGui;
		void BringHero();

		void BringUpgrades();

		void BringLoad();

	
		virtual void OnReturnTo();

	
		int DesiredNumCheckpoints;
		float DesiredLength;
		int DesiredHeroIndex;
	
		virtual void MyDraw();

	
		static std::wstring SeedStringToLoad;
		static bool ExitFreeplay;
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CUSTOMLEVEL_GUI
