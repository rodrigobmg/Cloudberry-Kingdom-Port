#ifndef NEWHERO
#define NEWHERO

#include <global_header.h>

namespace CloudberryKingdom
{
	struct NewHero_GUI : public GUI_Panel
	{
		virtual void OnAdd();

		boost::shared_ptr<EzText> text;
		NewHero_GUI( const std::wstring &str );
		boost::shared_ptr<NewHero_GUI> NewHero_GUI_Construct( const std::wstring &str );
		NewHero_GUI( const std::wstring &str, Vector2 shift, float scale, bool perma );
		boost::shared_ptr<NewHero_GUI> NewHero_GUI_Construct( const std::wstring &str, Vector2 shift, float scale, bool perma );

		static boost::shared_ptr<NewHero_GUI> HeroTitle( const std::wstring &str );

	
		bool Perma;
		void Init( const std::wstring &str, Vector2 shift, float scale, bool perma );

		int Count;
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef NEWHERO
