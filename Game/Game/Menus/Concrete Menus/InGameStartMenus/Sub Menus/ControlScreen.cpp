#include <global_header.h>

namespace CloudberryKingdom
{

	ControlScreen::ControlScreen( int Control ) : CkBaseMenu( false ) { }
	boost::shared_ptr<ControlScreen> ControlScreen::ControlScreen_Construct( int Control )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		this->setControl( Control );

		Constructor();

		return boost::static_pointer_cast<ControlScreen>( shared_from_this() );
	}

#if defined(PC_VERSION)
	boost::shared_ptr<QuadClass> ControlScreen::MakeQuad( Keys key )
	{
		boost::shared_ptr<QuadClass> quad = boost::make_shared<QuadClass>( ButtonString::KeyToTexture( key ), 90.f );
		MyPile->Add( quad );
		quad->Quad_Renamed.SetColor( CustomControlsMenu::SecondaryKeyColor );
		return quad;
	}
#endif

	void ControlScreen::Init()
	{
		 CkBaseMenu::Init();

		setPauseGame( true );

		SlideInFrom = SlideOutTo = PresetPos_LEFT;

		//ReturnToCallerDelay = SlideLength = 0;
		setSlideLength( 29 );
		DestinationScale *= 1.02f;

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();

		boost::shared_ptr<QuadClass> Backdrop = boost::make_shared<QuadClass>( std::wstring( L"Backplate_1230x740" ), 1500.f, true );
		Backdrop->Name = std::wstring( L"Backdrop" );
		MyPile->Add( Backdrop );

		ReturnToCallerDelay = 10;

		boost::shared_ptr<EzText> text;

	#if defined(PC_VERSION)
		text = boost::make_shared<EzText>( Localization::Words_QuickSpawn, Resources::Font_Grobold42 );
		MyPile->Add( text, std::wstring( L"quickspawn" ) );
		text->MyFloatColor = ColorHelper::Gray( .955f );

		text = boost::make_shared<EzText>( Localization::Words_PowerUpMenu, Resources::Font_Grobold42 );
		MyPile->Add( text, std::wstring( L"powerups" ) );
		text->MyFloatColor = ColorHelper::Gray( .955f );

		text = boost::make_shared<EzText>( Localization::Words_Menu, Resources::Font_Grobold42 );
		MyPile->Add( text, std::wstring( L"menu" ) );
		text->MyFloatColor = CampaignHelper::DifficultyColor[ 1 ].ToVector4();

		text = boost::make_shared<EzText>( Localization::Words_Accept, Resources::Font_Grobold42 );
		MyPile->Add( text, std::wstring( L"accept" ) );
		text->MyFloatColor = Menu::DefaultMenuInfo::UnselectedNextColor;
		text->MyFloatColor = Menu::DefaultMenuInfo::SelectedNextColor;

		text = boost::make_shared<EzText>( Localization::Words_Back, Resources::Font_Grobold42 );
		MyPile->Add( text, std::wstring( L"back" ) );
		text->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
		text->MyFloatColor = Menu::DefaultMenuInfo::UnselectedBackColor;

		text = boost::make_shared<EzText>( std::wstring( L"b" ), Resources::Font_Grobold42 );
		text->SubstituteText( std::wstring( L"<" ) );
		MyPile->Add( text, std::wstring( L"split" ) );

		boost::shared_ptr<QuadClass> q;

		q = boost::make_shared<QuadClass>( std::wstring( L"Enter_Key" ) );
		q->ScaleXToMatchRatio( 130 );
		MyPile->Add( q, std::wstring( L"enter" ) );

		q = boost::make_shared<QuadClass>( std::wstring( L"Esc_Key" ) );
		q->ScaleXToMatchRatio( 130 );
		MyPile->Add( q, std::wstring( L"esc" ) );

		q = boost::make_shared<QuadClass>( std::wstring( L"Backspace_Key" ) );
		q->ScaleXToMatchRatio( 130 );
		MyPile->Add( q, std::wstring( L"backspace" ) );

		q = boost::make_shared<QuadClass>( std::wstring( L"Space_Key" ) );
		q->ScaleXToMatchRatio( 130 );
		MyPile->Add( q, std::wstring( L"space" ) );

		SetPos();
	#endif
	}

#if defined(PC_VERSION)
	void ControlScreen::SetPos()
	{
		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( std::wstring( L"quickspawn" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -288.0965f, 435.3178f ) );
			_t->setScale( 1.06f );
		}
		_t = MyPile->FindEzText( std::wstring( L"powerups" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -267.0644f, 133.7302f ) );
			_t->setScale( 1.06f );
		}
		_t = MyPile->FindEzText( std::wstring( L"menu" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -280.1582f, 731.7462f ) );
			_t->setScale( 1.06f );
		}
		_t = MyPile->FindEzText( std::wstring( L"accept" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -286.109f, -156.3493f ) );
			_t->setScale( 1.06f );
		}
		_t = MyPile->FindEzText( std::wstring( L"back" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -264.2847f, -432.5391f ) );
			_t->setScale( 1.06f );
		}
		_t = MyPile->FindEzText( std::wstring( L"split" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -536.5085f, 14.28584f ) );
			_t->setScale( 1.46f );
		}

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( std::wstring( L"Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1500, 902.2556f ) );
		}
		_q = MyPile->FindQuad( std::wstring( L"enter" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -771.4287f, -234.9209f ) );
			_q->setSize( Vector2( 271.0638f, 130 ) );
		}
		_q = MyPile->FindQuad( std::wstring( L"esc" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -638.8887f, 520.2384f ) );
			_q->setSize( Vector2( 138.2979f, 130 ) );
		}
		_q = MyPile->FindQuad( std::wstring( L"backspace" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -773.8103f, -603.5712f ) );
			_q->setSize( Vector2( 271.0638f, 130 ) );
		}
		_q = MyPile->FindQuad( std::wstring( L"space" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -768.6523f, 205.9521f ) );
			_q->setSize( Vector2( 271.0638f, 130 ) );
		}

		MyPile->setPos( Vector2( 0, 0 ) );
	}
#endif

	void ControlScreen::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( !Active )
			return;

		if ( ButtonCheck::State( ControllerButtons_A, -1 ).Pressed || ButtonCheck::State( ControllerButtons_B, -1 ).Pressed )
		{
			Active = false;
			ReturnToCaller();
		}
	}
}
