#ifndef BOUNCY
#define BOUNCY

#include <small_header.h>

//#include "Game/Localization.h"
//#include "Core/Sound/EzSound.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/Icon.h"
//#include "Game/Objects/Bob/Bob.h"
#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct BobPhsxBouncy : public BobPhsxNormal
	{
	
		virtual ~BobPhsxBouncy()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxBouncy" );
#endif
		}


		static void InitializeStatics();

		// Singleton
	
		virtual void InitSingleton();
	
		static boost::shared_ptr<BobPhsxBouncy> instance;
	
		const static boost::shared_ptr<BobPhsxBouncy> &getInstance();

		virtual boost::shared_ptr<BobPhsx> Clone();
		void CopyTo( const boost::shared_ptr<BobPhsxBouncy> &bob );

		// Instancable struct
	
		bool InitializedAnim;

	
		BobPhsxBouncy();

		virtual void Init( const boost::shared_ptr<Bob> &bob );

		boost::shared_ptr<EzSound> DullSound;

		virtual void DefaultValues();

		virtual void DuckingPhsx();

		virtual void UpdateReadyToJump();

		//float FakeVel = 0;
	
		float SuperBounce;
		int SuperBounceGraceCount;
		int SuperBounceGrace;
	
		void PlayJumpSound();

		virtual void Jump();

		virtual void AnimStep();

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef BOUNCY
