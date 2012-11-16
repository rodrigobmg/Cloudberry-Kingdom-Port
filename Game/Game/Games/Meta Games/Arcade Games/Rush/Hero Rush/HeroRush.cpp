﻿#include "HeroRush.h"
#include "Game/Level/Make/CloudberryKingdom.LevelSeedData.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush_Tutorial.h"
#include "Game/Games/GameType.h"
#include "Game/Player/Awardments/Awardment.h"
#include "Game/Tools/Tools.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/CoinMod.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include "Game/Objects/In Game Objects/Grab/Coin__Auto.h"
#include "Game/Localization.h"
#include "Game/Objects/Game Objects/GameObjects/DoorIcon.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/Door/Sign.h"
#include "Game/Objects/Game Objects/GameObjects/MultiplierUp.h"
#include "Game/Objects/Game Objects/GameObjects/SuperCheer.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Player/Hero Physics/Base.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Games/Meta Games/Challenges/_Regular.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	Challenge_HeroRush::OnSwapLambda::OnSwapLambda( const std::shared_ptr<Challenge_HeroRush> &ch )
	{
		this->ch = ch;
	}

	void Challenge_HeroRush::OnSwapLambda::Apply( const std::shared_ptr<LevelSeedData> &data )
	{
		data->MyGame->AddGameObject( std::make_shared<HeroRush_Tutorial>( ch ) );
	}

	Challenge_HeroRush::ScoreMultiplierHelper::ScoreMultiplierHelper( float multiplier )
	{
		this->multiplier = multiplier;
	}

	void Challenge_HeroRush::ScoreMultiplierHelper::Apply( const std::shared_ptr<GameData> &game )
	{
		game->ScoreMultiplier *= multiplier;
	}

	Challenge_HeroRush::AdditionalPreStartOnSwapToLevelHelper::AdditionalPreStartOnSwapToLevelHelper( const std::shared_ptr<Challenge_HeroRush> &chr )
	{
		this->chr = chr;
	}

	void Challenge_HeroRush::AdditionalPreStartOnSwapToLevelHelper::Apply( int levelindex )
	{
		Awardments::CheckForAward_HeroRush2Unlock( levelindex - chr->StartIndex );

		// Add hero icon to exit door
		chr->MakeExitDoorIcon( levelindex );

		// Score multiplier, x1, x1.5, x2, ... for levels 0, 20, 40, ...
		float multiplier = 1 + ( ( levelindex + 1 ) / chr->LevelsPerDifficulty ) *.5f;
		Tools::CurGameData->OnCalculateScoreMultiplier->Add( std::make_shared<ScoreMultiplierHelper>( multiplier ) );

		// Mod number of coins
		std::shared_ptr<CoinMod> mod = std::make_shared<CoinMod>( chr->Timer );
		mod->LevelMax = 17;
		mod->ParMultiplier_Start = 1.6f;
		mod->ParMultiplier_End = 1;
		mod->CoinControl( Tools::CurGameData->MyLevel, ( levelindex + 1 ) % chr->LevelsPerDifficulty );

		// Reset sooner after death
		Tools::CurGameData->SetDeathTime( GameData::DeathTime_FAST );

		// Modify the timer
		chr->SetTimerProperties( levelindex / chr->LevelsPerDifficulty );

		chr->OnSwapTo_GUI( levelindex );
	}

	void Challenge_HeroRush::MakeMyModParamsHelper::Apply( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &p )
	{
		std::shared_ptr<Coin_Parameters> Params = static_cast<Coin_Parameters*>( p->Style_FIND_PARAMS( Coin_AutoGen::getInstance() ) );
		Params->FillType = Coin_Parameters::FillTypes_RUSH;
	}

const std::shared_ptr<Challenge_HeroRush> Challenge_HeroRush::instance = std::make_shared<Challenge_HeroRush>();

	const std::shared_ptr<Challenge_HeroRush> &Challenge_HeroRush::getInstance() const
	{
		return instance;
	}

	Challenge_HeroRush::Challenge_HeroRush()
	{
		InitializeInstanceFields();
		GameTypeId = 1;
		MenuName = Name = Localization::Words_HERO_RUSH;
	}

const int tempVector[] = { 20, 15, 10, 10, 10 };
std::vector<int> Challenge_HeroRush::MaxTime_ByDifficulty = std::vector<int>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
const int tempVector2[] = { 15, 12, 10, 10, 10 };
std::vector<int> Challenge_HeroRush::StartTime_ByDifficulty = std::vector<int>( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) );

	void Challenge_HeroRush::SetTimerProperties( int Difficulty )
	{
		Difficulty = __min( Difficulty, MaxTime_ByDifficulty.size() - 1 );

		Timer->CoinTimeValue = static_cast<int>( 62 * 1.75f );

		if ( Difficulty >= MaxTime_ByDifficulty.size() )
			Timer->MaxTime = MaxTime_ByDifficulty[ MaxTime_ByDifficulty.size() - 1 ];
		else
			Timer->MaxTime = 62 * ( MaxTime_ByDifficulty[ Difficulty ] + 0 ) - 1;
	}

	void Challenge_HeroRush::PreStart_Tutorial( bool TemporarySkip )
	{
		HeroRush_Tutorial::TemporarySkip = TemporarySkip;
		MyStringWorld->OnSwapToFirstLevel->Add( std::make_shared<OnSwapLambda>( this ) );
	}

	void Challenge_HeroRush::MakeExitDoorIcon( int levelindex )
	{
		Vector2 shift = Vector2( 0, 470 );

		Tools::CurGameData->AddGameObject( std::make_shared<DoorIcon>( GetHero( levelindex + 1 - StartIndex ), Tools::CurLevel->getFinalDoor()->getPos() + shift, 1 ) );

		// Delete the exit sign
		for ( std::vector<ObjectBase*>::const_iterator obj = Tools::CurLevel->Objects.begin(); obj != Tools::CurLevel->Objects.end(); ++obj )
			if ( dynamic_cast<Sign*>( *obj ) != 0 )
				( *obj )->getCore()->MarkedForDeletion = true;
	}

	void Challenge_HeroRush::AdditionalPreStart()
	{
		Rush::AdditionalPreStart();

		// Set timer values
		int Difficulty = ( StartIndex + 1 ) / LevelsPerDifficulty;
		SetTimerProperties( Difficulty );

		if ( Difficulty >= StartTime_ByDifficulty.size() )
			Timer->setTime( 62 * StartTime_ByDifficulty[ StartTime_ByDifficulty.size() - 1 ] );
		else
			Timer->setTime( 62 * StartTime_ByDifficulty[ Difficulty ] );

		// Tutorial
		PreStart_Tutorial( StartIndex > 0 );

		// When a new level is swapped to...
		MyStringWorld->OnSwapToLevel->Add( std::make_shared<AdditionalPreStartOnSwapToLevelHelper>( this ) );
	}

	void Challenge_HeroRush::OnSwapTo_GUI( int levelindex )
	{
		// Multiplier increase text
		if ( ( levelindex + 1 ) % LevelsPerDifficulty == 0 )
			Tools::CurGameData->AddGameObject( std::make_shared<MultiplierUp>() );

		// Cheering berries (20, 40, 60, ...)
		if ( ( levelindex + 1 ) % LevelsPerDifficulty == 0 && levelindex != StartIndex )
			Tools::CurGameData->AddGameObject( std::make_shared<SuperCheer>( 1 ) );
	}

	std::shared_ptr<LevelSeedData> Challenge_HeroRush::GetSeed( int Index )
	{
		float difficulty = CoreMath::MultiLerpRestrict( Index / static_cast<float>( LevelsPerDifficulty ), -.5f, 0, 1, 2, 2.5f, 3, 3.5f, 4, 4.5f );
		std::shared_ptr<CloudberryKingdom::LevelSeedData> seed = Make( Index, difficulty );

		return seed;
	}

const BobPhsx* tempVector3[] = { BobPhsxNormal::getInstance(), BobPhsxJetman::getInstance(), BobPhsxDouble::getInstance(), BobPhsxSmall::getInstance(), BobPhsxWheel::getInstance(), BobPhsxSpaceship::getInstance(), BobPhsxBouncy::getInstance(), BobPhsxBig::getInstance() };
std::vector<BobPhsx*> Challenge_HeroRush::HeroTypes = std::vector<BobPhsx*>( tempVector3, tempVector3 + sizeof( tempVector3 ) / sizeof( tempVector3[ 0 ] ) );

	std::shared_ptr<BobPhsx> Challenge_HeroRush::GetHero( int i )
	{
		return HeroTypes[ i % HeroTypes.size() ];
	}

const std::wstring tempVector4[] = { _T( "sea" ), _T( "hills" ), _T( "forest" ), _T( "cloud" ), _T( "cave" ), _T( "castle" ) };
std::vector<std::wstring> Challenge_HeroRush::tilesets = std::vector<std::wstring>( tempVector4, tempVector4 + sizeof( tempVector4 ) / sizeof( tempVector4[ 0 ] ) );

	std::shared_ptr<TileSet> Challenge_HeroRush::GetTileSet( int i )
	{
		return tilesets[ ( i / LevelsPerTileset ) % tilesets.size() ];
	}

	std::shared_ptr<LevelSeedData> Challenge_HeroRush::Make( int Index, float Difficulty )
	{
		std::shared_ptr<BobPhsx> hero = GetHero( Index - StartIndex );

		// Adjust the length. Longer for higher levels.
		int Length;
		if ( Index == 0 || ( Index + 1 ) % LevelsPerDifficulty == 0 )
			Length = LevelLength_Short;
		else
		{
			float t = ( ( ( Index + 1 ) % LevelsPerDifficulty ) / 5 + 1 ) / 5;
			Length = CoreMath::LerpRestrict( LevelLength_Short, LevelLength_Long, t );
		}

		// Create the LevelSeedData
		std::shared_ptr<LevelSeedData> data = RegularLevel::HeroLevel( Difficulty, hero, Length );
		data->SetTileSet( GetTileSet( Index - StartIndex ) );

		// Adjust the piece seed data
		for ( std::vector<PieceSeedData*>::const_iterator piece = data->PieceSeeds.begin(); piece != data->PieceSeeds.end(); ++piece )
		{
			// Shorten the initial computer delay
			( *piece )->Style_COMPUTER_WAIT_LENGTH_RANGE = Vector2( 4, 23 );

			// Only one path
			( *piece )->Paths = 1;
			( *piece )->LockNumOfPaths = true;

			( *piece )->Style_MY_MOD_PARAMS->Add( std::make_shared<MakeMyModParamsHelper>() );
		}

		return data;
	}

	void Challenge_HeroRush::InitializeInstanceFields()
	{
		LevelsPerDifficulty = 20;
		LevelsPerTileset = 4;
		LevelLength_Short = 2150;
		LevelLength_Long = 3900;
	}
}