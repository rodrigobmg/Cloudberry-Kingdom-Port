#include <global_header.h>
#include <Hacks\List.h>

namespace CloudberryKingdom
{

        void CkBaseMenu::EnableBounce()
        {
            MasterAlpha = 1;

            zoom = boost::make_shared<FancyVector2>();
            UseBounce = true;
        }

        void CkBaseMenu::BouncDraw()
        {
            if (zoom != 0)
            {
                Vector2 v = zoom->Update();
                MasterAlpha = v.X * v.X;

                MyGame->getCam()->setZoom( .001f * v );
                MyGame->getCam()->SetVertexCamera();
                EzText.ZoomWithCamera_Override = true;
            }
            else
            {
                MasterAlpha = 1.0f;
            }

            MyPile->setAlpha( MasterAlpha );
        }

        void CkBaseMenu::MyDraw()
        {
            if (UseBounce)
                BouncDraw();

			GUI_Panel::MyDraw();
        }












	CkBaseMenu::ReturnToCallerProxy::ReturnToCallerProxy( const boost::shared_ptr<CkBaseMenu> &cbm )
	{
		this->cbm = cbm;
	}

	void CkBaseMenu::ReturnToCallerProxy::Apply()
	{
		cbm->ReturnToCaller();
	}

	CkBaseMenu::ReturnToCallerProxy1::ReturnToCallerProxy1( const boost::shared_ptr<CkBaseMenu> &cbm )
	{
		this->cbm = cbm;
	}

	void CkBaseMenu::ReturnToCallerProxy1::Apply( const boost::shared_ptr<MenuItem> &dummy )
	{
		cbm->ReturnToCaller();
	}

	CkBaseMenu::MakeBackButtonHelper::MakeBackButtonHelper( const boost::shared_ptr<CkBaseMenu> &bm )
	{
		this->bm = bm;
	}

	void CkBaseMenu::MakeBackButtonHelper::Apply( const boost::shared_ptr<MenuItem> &menuitem )
	{
		bm->_MakeBackGo(menuitem);
	}

	void CkBaseMenu::MakeDarkBack()
	{
		// Make the dark back
		DarkBack = boost::make_shared<QuadClass>( std::wstring( L"White" ) );
		DarkBack->Quad_Renamed.SetColor( ColorHelper::GrayColor( .25f ) );
		DarkBack->setAlpha( 0 );
		DarkBack->Fade( .1f );
		DarkBack->MaxAlpha = .5f;
		DarkBack->FullScreen( Tools::getCurCamera() );
		DarkBack->setPos( Vector2() );
		DarkBack->Scale( 5 );
		MyPile->Add( DarkBack, std::wstring( L"Dark" ) );
	}

	void CkBaseMenu::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		if ( item->MyText == 0 )
			return;

		SetTextProperties( item->MyText );
		SetSelectedTextProperties( item->MySelectedText );
	}

	void CkBaseMenu::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		text->MyFloatColor = Vector4( .6f,.6f,.6f, 1 );
		text->OutlineColor = Vector4( 0, 0, 0, 1 );

		text->Shadow = true;
		text->ShadowColor = Color( .2f,.2f,.2f, 1 );
		text->ShadowOffset = Vector2( 12, 12 );

		text->setScale( FontScale *.9f );
	}

	void CkBaseMenu::SetTextProperties( const boost::shared_ptr<EzText> &text )
	{
		text->MyFloatColor = ( bColor( 184, 231, 231 ) ).ToVector4();

		text->setScale( FontScale );

		text->Shadow = ItemShadows;
		text->ShadowColor = Color( .2f,.2f,.2f, 1 );
		text->ShadowOffset = Vector2( 12, 12 );
	}

	void CkBaseMenu::SetSelectedTextProperties( const boost::shared_ptr<EzText> &text )
	{
		text->MyFloatColor = ( bColor( 246, 214, 33 ) ).ToVector4();
		//text.MyFloatColor = new Color(50, 220, 50).ToVector4();

		text->setScale( FontScale );

		text->Shadow = ItemShadows;
		text->ShadowColor = Color( .2f,.2f,.2f, 1 );
		text->ShadowOffset = Vector2( 12, 12 );
	}

	void CkBaseMenu::AddItem( const boost::shared_ptr<MenuItem> &item )
	{
		SetItemProperties( item );

		item->Pos = ItemPos;
		item->SelectedPos = ItemPos + SelectedItemShift;

		ItemPos += PosAdd;

		MyMenu->Add( item );
	}

	void CkBaseMenu::setSlideLength( const int &value )
	{
		GUI_Panel::setSlideLength( value );
		if ( getTopPanel() != 0 )
			getTopPanel()->setSlideLength(value);
		if ( getRightPanel() != 0 )
			getRightPanel()->setSlideLength(value);
	}

	void CkBaseMenu::Init()
	{
		GUI_Panel::Init();

		// Sounds
		SelectSound = Menu::DefaultMenuInfo::Menu_Select_Sound;
		BackSound = Menu::DefaultMenuInfo::Menu_Back_Sound;

		// Delays
		Defaults();
	}

	void CkBaseMenu::DefaultDelays()
	{
		ReturnToCallerDelay = 40;
		CallDelay = 25;
	}

	void CkBaseMenu::DefaultSlides()
	{
		setSlideLength( 38 );
	}

	void CkBaseMenu::Defaults()
	{
		DefaultDelays();
		DefaultSlides();
	}

	void CkBaseMenu::NoDelays()
	{
		setSlideLength( 0 );
		CallDelay = 0;
		ReturnToCallerDelay = 0;
	}

	void CkBaseMenu::FastDelays()
	{
		CallDelay = 18;
		ReturnToCallerDelay = 26;
	}

	void CkBaseMenu::FastSlides()
	{
		setSlideLength( 33 );
	}

	void CkBaseMenu::Fast()
	{
		FastDelays();
		FastSlides();
	}

	void CkBaseMenu::CategoryDelays()
	{
		ReturnToCallerDelay = 16;
		SlideInLength = 25;
		SlideOutLength = 24;

		CallDelay = 18;
	}

	void CkBaseMenu::Call( const boost::shared_ptr<GUI_Panel> &child, int Delay )
	{
		GUI_Panel::Call( child, Delay );

        if ( SelectSound != 0 && !SkipCallSound )
            SelectSound->Play();
        SkipCallSound = false;

		if ( CallToLeft )
		{
			Hide( PresetPos_LEFT );
		}
	}

	void CkBaseMenu::OnReturnTo()
	{
        if (UseBounce)
        {
            GUI_Panel::OnReturnTo();
            RegularSlideOut( PresetPos::PresetPos_RIGHTRight, 0 );
            BubbleUp();
        }
        else
        {
			if ( CallToLeft )
			{
				// Reset the menu's selected item's oscillate
				if ( MyMenu != 0 )
					MyMenu->getCurItem()->OnSelect();

				// Activate and show the panel
				Active = true;

				if ( !Hid )
					return;
				GUI_Panel::Show();
				this->SlideOut( PresetPos_LEFT, 0 );
				this->SlideIn();
			}
			else
				GUI_Panel::OnReturnTo();
		}
	}

	void CkBaseMenu::ReturnToCaller()
	{
		ReturnToCaller( true );
	}

	void CkBaseMenu::ReturnToCaller( bool PlaySound )
	{
		GUI_Panel::ReturnToCaller();

		if ( DarkBack != 0 )
			DarkBack->Fade( -.1f );

		if ( PlaySound && BackSound != 0 )
			BackSound->Play();
	}

	void CkBaseMenu::setRightPanel( const boost::shared_ptr<GUI_Panel> &value )
	{
		_RightPanel = value;
		_RightPanel->CopySlideLengths( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
	}

	const boost::shared_ptr<GUI_Panel> &CkBaseMenu::getRightPanel() const
	{
		return _RightPanel;
	}

	void CkBaseMenu::setTopPanel( const boost::shared_ptr<GUI_Panel> &value )
	{
		_TopPanel = value;
		_TopPanel->CopySlideLengths( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
	}

	const boost::shared_ptr<GUI_Panel> &CkBaseMenu::getTopPanel() const
	{
		return _TopPanel;
	}

	void CkBaseMenu::OnAdd()
	{
		GUI_Panel::OnAdd();

		if ( getTopPanel() != 0 )
			MyGame->AddGameObject( getTopPanel() );
		if ( getRightPanel() != 0 )
			MyGame->AddGameObject( getRightPanel() );

		//SlideLength = 38;

		Show();

        BubbleUp();
    }

    void CkBaseMenu::BubbleUp()
    {
        if ( zoom != 0 )
        {
            SlideIn( 0 );
			Vector2 vals[] = { Vector2(0.98f), Vector2(1.02f), Vector2(.99f), Vector2(1.005f), Vector2(1.0f) };
            zoom->MultiLerp( 5, VecFromArray( vals ) );
        }
    }

    void CkBaseMenu::BubbleDown()
    {
		Vector2 vals[] = { Vector2(1.0f), Vector2(1.01f), Vector2(.9f), Vector2(.4f), Vector2(0.0f) };
        zoom->MultiLerp( 5, VecFromArray( vals ) );
    }

	void CkBaseMenu::ReleaseBody()
	{
		GUI_Panel::ReleaseBody();

		if ( getTopPanel() != 0 )
			getTopPanel()->Release();
		if ( getRightPanel() != 0 )
			getRightPanel()->Release();
	}

	void CkBaseMenu::Show()
	{
		if ( !Hid )
			return;

		GUI_Panel::Show();

		SlideOut( SlideInFrom, 0 );

		SlideIn();
	}

	void CkBaseMenu::SlideIn( int Frames )
	{
		GUI_Panel::SlideIn( Frames );

		if ( getRightPanel() != 0 )
			SlideIn_RightPanel( Frames );

		if ( getTopPanel() != 0 )
		{
			getTopPanel()->SlideOut(PresetPos_RIGHT, 0);
			getTopPanel()->SlideIn();
		}
	}

	void CkBaseMenu::SlideIn_RightPanel( int Frames )
	{
		getRightPanel()->SlideOut(PresetPos_RIGHT, 0);
		getRightPanel()->SlideIn();
	}

	void CkBaseMenu::SlideOut( GUI_Panel::PresetPos Preset, int Frames )
    {
        if (UseBounce)
            BounceSlideOut(Preset, Frames);
        else
            RegularSlideOut(Preset, Frames);
    }

    void CkBaseMenu::BounceSlideOut( GUI_Panel::PresetPos Preset, int Frames )
    {
        ReturnToCallerDelay = 15;

        if (Frames == 0)
        {
            RegularSlideOut( Preset, Frames );
            return;
        }

        BubbleDown();
        MyGame->WaitThenDo( 15, boost::make_shared<Release>( shared_from_this() ) );

        Active = true;

        ReleaseWhenDone = false;
        ReleaseWhenDoneScaling = false;
    }

	CkBaseMenu::ReleaseProxy::ReleaseProxy( boost::shared_ptr<CkBaseMenu> _bm )
	{
		bm = _bm;
	}
	void CkBaseMenu::ReleaseProxy::Apply()
	{
	}

    void CkBaseMenu::RegularSlideOut( GUI_Panel::PresetPos Preset, int Frames )
	{
		GUI_Panel::SlideOut( Preset, Frames );

		if ( getRightPanel() != 0 )
			SlideOut_RightPanel( Preset, Frames );
		if ( getTopPanel() != 0 )
			getTopPanel()->SlideOut(PresetPos_RIGHT, Frames);
	}

	void CkBaseMenu::SlideOut_RightPanel( GUI_Panel::PresetPos Preset, int Frames )
	{
		getRightPanel()->SlideOut(PresetPos_RIGHT, Frames);
	}

	void CkBaseMenu::Hide()
	{
		Hide( SlideOutTo );
	}

	void CkBaseMenu::Hide( PresetPos pos )
	{
		Hide( pos, -1 );
	}

	void CkBaseMenu::Hide( PresetPos pos, int frames )
	{
		GUI_Panel::Hide();

		if ( frames == -1 )
			SlideOut( pos );
		else
			SlideOut( pos, frames );
	}

	void CkBaseMenu::MakeStaticBackButton()
	{
		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getBack(), 90, L"Button_Back" ) );
		MyPile->Add( boost::make_shared<QuadClass>( L"BackArrow2", L"BackArrow" ) );
	}

	boost::shared_ptr<MenuItem> CkBaseMenu::MakeBackButton()
	{
		return MakeBackButton( Localization::Words_Back );
	}

	boost::shared_ptr<MenuItem> CkBaseMenu::MakeBackButton( Localization::Words Word )
	{
		boost::shared_ptr<MenuItem> item;

	#if defined(PC_VERSION)
        if (ButtonCheck.ControllerInUse)
            item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( ButtonString::Back(86) + L" " + Localization::WordString( Word ) ) ) );
        else
        {
            //item = new MenuItem(new EzText(ButtonString.Back(86) + Localization.WordString(Word), ItemFont));
            item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::WordString( Word ), ItemFont ) ) );
        }
	#else
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( ButtonString::Back( 86 ) + std::wstring( L" " ) + Localization::WordString( Word ) ) ) );
	#endif

		item->setGo( boost::make_shared<MakeBackButtonHelper>( boost::static_pointer_cast<CkBaseMenu>( shared_from_this() ) ) );
		item->Name = std::wstring( L"Back" );
		AddItem( item );
		item->SelectSound.reset();
		item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
		item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedBackColor;

		return item;
	}

    void CkBaseMenu::_MakeBackGo( boost::shared_ptr<MenuItem> item )
    {
        item->MyMenu->OnB->Apply( item->MyMenu );
    }

	void CkBaseMenu::MakeBackdrop( const boost::shared_ptr<Menu> &menu, Vector2 TR, Vector2 BL )
	{
		menu->MyPieceQuad = boost::make_shared<PieceQuad>();
		menu->MyPieceQuadTemplate = MenuTemplate;
		menu->TR = TR;
		menu->BL = BL;
		menu->ResetPieces();

		SetBackdropProperties( menu->MyPieceQuad );
	}

boost::shared_ptr<PieceQuad> CkBaseMenu::MenuTemplate = 0;

	void CkBaseMenu::MakeBackdrop( Vector2 TR, Vector2 BL )
	{
		MakeBackdrop( MyMenu, TR, BL );
	}

	void CkBaseMenu::SetBackdropProperties( const boost::shared_ptr<PieceQuad> &piecequad )
	{
		piecequad->SetAlpha( .7f );
	}

int CkBaseMenu::DefaultMenuLayer = Level::LastInLevelDrawLayer;

	CkBaseMenu::CkBaseMenu() :
        MasterAlpha( 0 ),
        UseBounce( false ),
		FontScale( 0 ),
		ItemShadows( true ),
		CallToLeft( false ),
		SlideInFrom( PresetPos_LEFT ),
		SlideOutTo( PresetPos_LEFT )
	{
	}
	boost::shared_ptr<CkBaseMenu> CkBaseMenu::CkBaseMenu_Construct()
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();
		
		getCore()->DrawLayer = DefaultMenuLayer;

		return boost::static_pointer_cast<CkBaseMenu>( shared_from_this() );
	}

	CkBaseMenu::CkBaseMenu( bool CallBaseConstructor ) : GUI_Panel( CallBaseConstructor ),
		FontScale( 0 ),
		ItemShadows( true ),
		CallToLeft( false ),
		SlideInFrom( PresetPos_LEFT ),
		SlideOutTo( PresetPos_LEFT )
	{
	}
	boost::shared_ptr<CkBaseMenu> CkBaseMenu::CkBaseMenu_Construct( bool CallBaseConstructor )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct( CallBaseConstructor );
		
		getCore()->DrawLayer = DefaultMenuLayer;

		return boost::static_pointer_cast<CkBaseMenu>( shared_from_this() );
	}

	void CkBaseMenu::Draw()
	{
		GUI_Panel::Draw();

		if ( DarkBack != 0 && !IsOnScreen )
			DarkBack->Draw();
	}

	void CkBaseMenu::InitializeInstanceFields()
	{
		SkipCallSound = false;

		ItemPos = Vector2( -808, 110 );
		PosAdd = Vector2( 0, -151 ) * 1.181f;
		ItemFont = Resources::Font_Grobold42;
		FontScale = .75f;
		ItemShadows = true;
		SelectedItemShift = Vector2( 0, 0 );
		CallToLeft = false;
		SlideInFrom = PresetPos_LEFT;
		SlideOutTo = PresetPos_LEFT;
	}
}
