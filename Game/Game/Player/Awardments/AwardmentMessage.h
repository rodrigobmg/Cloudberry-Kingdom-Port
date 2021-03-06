#ifndef AWARDMENTMESSAGE
#define AWARDMENTMESSAGE

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Player/Awardments/Awardment.h"
//#include "Game/Tools/Resources.h"


namespace CloudberryKingdom
{

	struct AwardmentMessage : public CkBaseMenu
	{

		virtual ~AwardmentMessage()
		{
#ifdef BOOST_BIN
			OnDestructor( "AwardmentMessage" );
#endif
		}


		using CkBaseMenu::SlideOut;
		using CkBaseMenu::SlideIn;
		using CkBaseMenu::Call;

		boost::shared_ptr<QuadClass> Backdrop;

	
		AwardmentMessage( const boost::shared_ptr<Awardment> &award );
		boost::shared_ptr<AwardmentMessage> AwardmentMessage_Construct( const boost::shared_ptr<Awardment> &award );

		void MakeText( std::wstring TitleWord, std::wstring DescriptionWord );
	
		virtual void MakeBackdrop();

	
		virtual void SlideIn( int Frames );

		virtual void SlideOut( PresetPos Preset, int Frames );

	
		boost::shared_ptr<EzText> Text;
	
		int Step;
		virtual void MyPhsxStep();

	
		static const int Duration = static_cast<int>( 2.3 * 62 );
	
		bool ShouldDie();

	
		void Kill();
		void Kill( bool sound );

	
		void InitializeInstanceFields();
	};

    struct HeroUnlockedMessage : public AwardmentMessage
    {

        HeroUnlockedMessage();
		boost::shared_ptr<HeroUnlockedMessage> HeroUnlockedMessage_Construct( );

	};

}


#endif	//#ifndef AWARDMENTMESSAGE
