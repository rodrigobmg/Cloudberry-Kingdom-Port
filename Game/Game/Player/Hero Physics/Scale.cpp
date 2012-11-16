﻿#include "Scale.h"
#include "Game/Player/Hero Physics/Base.h"
#include "Game/Player/Cape.h"
#include "Game/Localization.h"
#include "Game/Objects/Icon.h"
#include "Game/Tools/Tools.h"

using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{

	void BobPhsxScale::Set( const std::shared_ptr<BobPhsx> &phsx )
	{
		phsx->Oscillate_Renamed = true;
		phsx->ForceDown = -7.5f;
		phsx->CapePrototype = Cape::CapeType_NORMAL;

		phsx->DollCamZoomMod = .535f;
	}

	void BobPhsxScale::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 0, 2, 0, 0 );
		Name = Localization::Words_PHASE_BOB;
		Adjective = _T( "phasing" );
		Icon = std::make_shared<PictureIcon>( Tools::TextureWad->FindByName( _T( "HeroIcon_Phase" ) ), Color::White, 1.1f * DefaultIconWidth );
	}

const std::shared_ptr<BobPhsxScale> BobPhsxScale::instance = std::make_shared<BobPhsxScale>();

	const std::shared_ptr<BobPhsxScale> &BobPhsxScale::getInstance() const
	{
		return instance;
	}

	BobPhsxScale::BobPhsxScale()
	{
		Set( this );
	}
}