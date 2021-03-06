#include <small_header.h>
#include "Game/Player/Hero Physics/Bouncy.h"

#include "Game/Localization.h"
#include "Core/Sound/EzSound.h"
#include "Game/Player/Hero Physics/Base.h"
#include "Game/Objects/Icon.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Player/Hero Physics/Normal.h"
#include "Game/Tools/Tools.h"


#include "Hacks/Queue.h"
#include <MasterHack.h>

#include "Core/Texture/EzTextureWad.h"
#include "Core/Sound/EzSoundWad.h"
#include "Game/Level/Level.h"
#include <Core/Animation/AnimQueue.h>

namespace CloudberryKingdom
{

	void BobPhsxBouncy::InitializeStatics()
	{
		BobPhsxBouncy::instance = boost::make_shared<BobPhsxBouncy>();
			InitBobPhsxSingleton( BobPhsxBouncy::instance );
	}

	// Statics
	boost::shared_ptr<BobPhsxBouncy> BobPhsxBouncy::instance;


	void BobPhsxBouncy::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 3, 0, 0, 0 );
		Name = Localization::Words_Bouncy;
		NameTemplate = std::wstring( L"bouncey bounce" );

		Icon = boost::make_shared<PictureIcon>( Tools::TextureWad->FindByName( std::wstring( L"Bob_Horse_0000" ) ), Color::White, 1.35875f * DefaultIconWidth );
		( boost::static_pointer_cast<PictureIcon>( Icon ) )->IconQuad->Quad_Renamed.Shift( Vector2( 0, -.035f ) );
	}

	const boost::shared_ptr<BobPhsxBouncy> &BobPhsxBouncy::getInstance()
	{
		return instance;
	}

	boost::shared_ptr<BobPhsx> BobPhsxBouncy::Clone()
	{
		boost::shared_ptr<BobPhsxBouncy> newBob = boost::make_shared<BobPhsxBouncy>();
			InitBobPhsxSingleton( newBob );
		CopyTo( newBob );
		return boost::static_pointer_cast<BobPhsx>( newBob );
	}

	void BobPhsxBouncy::CopyTo( const boost::shared_ptr<BobPhsxBouncy> &bob )
	{
		BobPhsxNormal::CopyTo( boost::static_pointer_cast<BobPhsxNormal>( bob ) );

		bob->InitializedAnim = InitializedAnim;
		bob->SuperBounce = SuperBounce;
		bob->SuperBounceGraceCount = SuperBounceGraceCount;
		bob->SuperBounceGrace = SuperBounceGrace;
	}


	BobPhsxBouncy::BobPhsxBouncy() :
		InitializedAnim( false ),
		SuperBounce( 0 ),
		SuperBounceGraceCount( 0 ),
		SuperBounceGrace( 0 )
	{
		InitializeInstanceFields();
		DefaultValues();
	}

	void BobPhsxBouncy::Init( const boost::shared_ptr<Bob> &bob )
	{
		BobPhsxNormal::Init( bob );

		InitializedAnim = false;
		MyBob->PlayerObject->Read( 24, 0 );

        MyBob->JumpSound = Tools::SoundWad->FindByName( L"BouncyJump" );
        DullSound = Tools::SoundWad->FindByName( L"BouncyJump_Small" );
	}

	void BobPhsxBouncy::DefaultValues()
	{
		BobPhsxNormal::DefaultValues();

		BlobMod = .4f;

		BobInitialJumpSpeedDucking = 24;
		BobInitialJumpSpeed = 40;
		BobJumpLength = 0;
		BobJumpAccel = 0;

		CapeOffset = Vector2( 0, 30 );
	}

	void BobPhsxBouncy::DuckingPhsx()
	{
		bool Down = MyBob->CurInput.xVec.Y < -.4f;
		if ( Down )
			Ducking = true;
		else
			Ducking = false;
	}

	void BobPhsxBouncy::UpdateReadyToJump()
	{
		if ( !OnGround && CurJump > 0 )
			BobPhsxNormal::UpdateReadyToJump();
		else
			ReadyToJump = true;
	}

    void BobPhsxBouncy::PlayJumpSound()
    {
        //base.PlayJumpSound();
    }

	void BobPhsxBouncy::Jump()
	{
		SuperBounceGrace = 9;
		if ( !OnGround && CurJump > 0 )
		{
			// Allow for super bounce a few frames after hitting the ground
			if ( getMyLevel()->PlayMode == 0 )
			{
				if ( MyBob->CurInput.A_Button && SuperBounceGraceCount > 0 )
				{
					//if ( getMyLevel()->PlayMode == 0 && !MyBob->CharacterSelect2 ) MyBob->JumpSound->Play();
					setyVel( getyVel() + SuperBounce );
					SuperBounceGraceCount = 0;
				}
				else
					SuperBounceGraceCount--;
			}

			BobPhsxNormal::Jump();
		}
		else
		{
			UpdateReadyToJump();

			if ( getCanJump() )
			{
				DoJump();

				if ( MyBob->CurInput.A_Button )
				{
					setyVel( getyVel() + SuperBounce );
					if ( getMyLevel()->PlayMode == 0 && !MyBob->CharacterSelect2 ) MyBob->JumpSound->Play();
				}
				else
				{
					if ( getMyLevel()->PlayMode == 0 && !MyBob->CharacterSelect2 )
					{
						DullSound->Play();
						SuperBounceGraceCount = SuperBounceGrace;
					}
				}
			}
		}
	}

	void BobPhsxBouncy::AnimStep()
	{
		if ( !InitializedAnim )
		{
			Clear( MyBob->PlayerObject->AnimQueue );
			//MyBob->PlayerObject->AnimQueue.clear();
			MyBob->PlayerObject->EnqueueAnimation( 24, 0, false );
			MyBob->PlayerObject->DequeueTransfers();

			InitializedAnim = true;
		}

		//if (MyBob.Core.Data.Velocity.Y > 10f && !OnGround && StartJumpAnim)
		if ( ShouldStartJumpAnim() )
		{
			Clear( MyBob->PlayerObject->AnimQueue );
			//MyBob->PlayerObject->AnimQueue.clear();
			MyBob->PlayerObject->EnqueueAnimation( 24, 0, false );
			MyBob->PlayerObject->DequeueTransfers();
			MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= .85f;

			StartJumpAnim = false;
		}

		if ( MyBob->IsSpriteBased )
			MyBob->PlayerObject->PlayUpdate( 1.f );
		else
			MyBob->PlayerObject->PlayUpdate( 1000.f / 60.f / 150.f );
	}

	void BobPhsxBouncy::InitializeInstanceFields()
	{
		SuperBounce = 18;
		SuperBounceGraceCount = 0;
		SuperBounceGrace = 10;
	}
}
