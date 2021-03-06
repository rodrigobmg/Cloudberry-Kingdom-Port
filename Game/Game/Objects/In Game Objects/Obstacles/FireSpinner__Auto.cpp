#include <small_header.h>

#include "Game/Objects/In Game Objects/Obstacles/FireSpinner__Auto.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Game/Level/Make/DifficultyHelper.h"
#include "Game/Level/Level.h"
#include "Game/Tilesets/TileSetInfo.h"
#include "Game/Collision Detection/AABox.h"
#include "Game/Collision Detection/FloatRectangle.h"
#include "Core/Tools/Random.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Tools/Recycler.h"

namespace CloudberryKingdom
{

	ParamInfo::ParamInfo( float MinValue, float MaxValue, float DefaultValue )
	{
		this->MinValue = MinValue;
		this->MaxValue = MaxValue;
		this->DefaultValue = DefaultValue;
	}

	void FireSpinner_Parameters::SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		boost::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		// General difficulty
		float FirespinnerLevel = PieceSeed->MyUpgrades1->Get( Upgrade_FIRE_SPINNER );
		if ( FirespinnerLevel > 6 )
			NumOffsets = 8;
		else
			NumOffsets = 4;

		BobWidthLevel = Param( PieceSeed );
		BobWidthLevel.SetVal( u->Get( Upgrade_FIRE_SPINNER ) );

		MinDist = Param( PieceSeed );
		MinDist.SetVal( DifficultyHelper::Interp159( 650, 270, 110, u->Get( Upgrade_FIRE_SPINNER ) ) );

		Length = Param( PieceSeed );
		Length.SetVal( 240 + 36 * u->Get( Upgrade_FIRE_SPINNER ) );

		Period = Param( PieceSeed );
		Period.SetVal( __max( 38, 150 + 13 * u->Get( Upgrade_FIRE_SPINNER ) - 13 * u->Get( Upgrade_SPEED ) ) );

		MinDensity = Param( PieceSeed );
		MinDensity.SetVal( u->Get( Upgrade_FIRE_SPINNER ) == 0 ? 0 : DifficultyHelper::Interp( 50, 80, u->Get( Upgrade_FIRE_SPINNER ) ) );

		MaxDensity = Param( PieceSeed );
		MaxDensity.SetVal( u->Get( Upgrade_FIRE_SPINNER ) == 0 ? 0 : DifficultyHelper::Interp( 50, 150, u->Get( Upgrade_FIRE_SPINNER ) ) );
	}

	FireSpinner_AutoGen::Cleanup_2Proxy::Cleanup_2Proxy( const boost::shared_ptr<FireSpinner_Parameters> &Params )
	{
		this->Params = Params;
	}

	Vector2 FireSpinner_AutoGen::Cleanup_2Proxy::Apply( const Vector2 &pos )
	{
		float dist = Params->MinDist.GetVal( pos );
		return Vector2( dist, dist );
	}

boost::shared_ptr<FireSpinner_AutoGen> FireSpinner_AutoGen::instance = boost::make_shared<FireSpinner_AutoGen>();

	const boost::shared_ptr<FireSpinner_AutoGen> &FireSpinner_AutoGen::getInstance()
	{
		return instance;
	}

	FireSpinner_AutoGen::FireSpinner_AutoGen()
	{
		Do_PreFill_2 = true;
		//Generators.AddGenerator(this);
	}

	boost::shared_ptr<AutoGen_Parameters> FireSpinner_AutoGen::SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<FireSpinner_Parameters> Params = boost::make_shared<FireSpinner_Parameters>();
		Params->SetParameters( data, level );

		return boost::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void FireSpinner_AutoGen::PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );

		// Get FireSpinner parameters
		boost::shared_ptr<FireSpinner_Parameters> Params = boost::static_pointer_cast<FireSpinner_Parameters>( level->getStyle()->FindParams( FireSpinner_AutoGen::getInstance() ) );

		float SpinnerTopOffset = level->getInfo()->Spinners->TopOffset;
		float SpinnerBottomOffset = level->getInfo()->Spinners->BottomOffset;

		for ( BlockVec::const_iterator block = level->Blocks.begin(); block != level->Blocks.end(); ++block )
		{
			if ( ( *block )->getCore()->Placed )
				continue;

			if ( ( *block )->getBlockCore()->Virgin )
				continue;
			if ( ( *block )->getBlockCore()->Finalized )
				continue;
			if ( ( *block )->getBlockCore()->MyType == ObjectType_LAVA_BLOCK )
				continue;

			// Add fire spinners
			float xdif = ( *block )->getBox()->Current->TR.X - (*block)->getBox()->Current->BL.X - 30;
			float density = level->getRnd()->RndFloat(Params->MinDensity.GetVal((*block)->getCore()->Data.Position), Params->MaxDensity.GetVal((*block)->getCore()->Data.Position));
			float average = static_cast<float>( static_cast<int>( xdif * density / 2000 ) );
			int n = static_cast<int>( average );
			if ( average < 1 )
				if ( level->getRnd()->Rnd->NextDouble() < average )
					n = 1;

			for ( int i = 0; i < n; i++ )
			{
				if ( xdif > 0 )
				{
					float x = static_cast<float>( level->getRnd()->Rnd->NextDouble() ) * xdif + (*block)->getBox()->Target->BL.X + 35;
					float y;
					if ( ( *block )->getBlockCore()->BlobsOnTop )
					{
						y = ( *block )->getBox()->Target->TR.Y + SpinnerTopOffset;
					}
					else
					{
						y = ( *block )->getBox()->Target->BL.Y + SpinnerBottomOffset;
					}

					if ( x > level->CurMakeData->PieceSeed->End.X - 400 )
						continue;

					boost::shared_ptr<FireSpinner> spinner;

					spinner = boost::static_pointer_cast<FireSpinner>( level->getRecycle()->GetObject(ObjectType_FIRE_SPINNER, true) );
					spinner->getCore()->StartData.Position = spinner->getCore()->Data.Position = Vector2(x, y);

					spinner->Orientation = 1;
					spinner->Radius = Params->Length.GetVal( ( *block )->getCore()->Data.Position );

					int Period = static_cast<int>( Params->Period.GetVal( ( *block )->getCore()->Data.Position ) );

					int NumOffsets = Params->NumOffsets;
					Period = static_cast<int>( Period / NumOffsets ) * NumOffsets;
					spinner->Period = Period;
					spinner->Offset = Params->ChooseOffset( Period, level->getRnd() );

					spinner->SetParentBlock( *block );

					level->AddObject( spinner );
				}
			}
		}
	}

	void FireSpinner_AutoGen::Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );

		// Get FireSpinner parameters
		boost::shared_ptr<FireSpinner_Parameters> Params = boost::static_pointer_cast<FireSpinner_Parameters>( level->getStyle()->FindParams( FireSpinner_AutoGen::getInstance() ) );

		level->Cleanup( ObjectType_FIRE_SPINNER, boost::make_shared<Cleanup_2Proxy>( Params ), BL, TR );
	}
}
