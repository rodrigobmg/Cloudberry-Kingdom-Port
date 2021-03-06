#ifndef LOADING
#define LOADING

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Text/EzText.h"
//#include "Core/Tools/ColorHelper.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/WrappedFloat.h"


namespace CloudberryKingdom
{

	struct ProgressBar
	{
	
		enum BarType
		{
			BarType_SCALE,
			BarType_REVEAL
		};
	
		BarType MyType;

		const Vector2 &getFull_BL() const;
		const Vector2 &getFull_TR() const;
		const Vector2 getCurrent_TR() const;

		boost::shared_ptr<DrawPile> MyPile;

		boost::shared_ptr<QuadClass> Outline, Fill;

		float PercentDone;
		float Width;

		const Vector2 &getPos() const;
		void setPos( const Vector2 &value );

		ProgressBar();

	
		void Initialize();

	
		void InitStandardBar();

		ProgressBar( const std::wstring &FillName, const std::wstring &OutlineName, float Width );

		void InitCustomBar( const std::wstring &FillName, const std::wstring &OutlineName, float Width );

		void SetPercent( float Percent );

		void Draw();

		void Draw( bool Selected );

	
		void InitializeInstanceFields();
	};

	struct InitialLoadingScreen
	{
	
		static void InitializeStatics();
	
		bool IsDone;

		boost::shared_ptr<EzText> Legal;

		boost::shared_ptr<SoundEffect> Whinney;

		boost::shared_ptr<DrawPile> MyPile;
		boost::shared_ptr<ProgressBar> MyProgressBar;

		int LogoCount;
		int LogoCount_Max;
		boost::shared_ptr<WrappedFloat> ResourceCount;

		boost::shared_ptr<QuadClass> BlackQuad, Splash;

	
		InitialLoadingScreen( const boost::shared_ptr<ContentManager> &Content, const boost::shared_ptr<WrappedFloat> &ResourceCount );

		static int TotalResources;

		bool Accelerate;
	
		int DoneCount;
	
		void PhsxStep();

	    int DrawCount;
        bool ReadyToFade;
	
		void Draw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LOADING
