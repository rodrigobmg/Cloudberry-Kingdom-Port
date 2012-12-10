﻿#ifndef COIN__AUTO
#define COIN__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Bob;
}

namespace CloudberryKingdom
{
	struct Level;
}

namespace CloudberryKingdom
{
	struct PieceSeedData;
}

namespace CloudberryKingdom
{
	struct AutoGen_Parameters;
}

namespace CloudberryKingdom
{
	struct ObjectBase;
}




namespace CloudberryKingdom
{
	struct Coin_Parameters : public AutoGen_Parameters
	{
	
		enum FillTypes
		{
			FillTypes_NONE,
			FillTypes_REGULAR,
			FillTypes_RUSH,
			FillTypes_COIN_GRAB
		};
	
		struct _Special
		{
		};
	
		bool Red;

		Param MinDist, PlaceDelay;

		FillTypes FillType;

		/// <summary> Whether coins should be placed on a grid lattice. </summary>
		bool Grid;
	
		Vector2 GridSpacing;
	
		Vector2 SnapToGrid( Vector2 pos );

		bool DoCleanup;

		/// <summary> The frame afterwhich coins can be placed. </summary>
		int StartFrame;

		/// <summary> Used to determine if a coin should be placed (Regular style) </summary>
		int Regular_Period, Regular_Offset, Regular_Period2, Regular_Offset2;
		/// <summary> Whehter a coin should be placed (Regular style) </summary>
		bool Regular_ReadyToPlace( const std::shared_ptr<Level> &level, const std::shared_ptr<Bob> &bob, int Step );

		bool CoinPlaced;

		Vector2 TR_Bound_Mod, BL_Bound_Mod;

		_Special Special;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		Coin_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	struct Coin_AutoGen : public AutoGen
	{
	
		enum BobPos
		{
			BobPos_CENTER,
			BobPos_HIGH,
			BobPos_LOW,
			BobPos_REGULAR
		};
	
		static const std::shared_ptr<Coin_AutoGen> instance;
	
		const static std::shared_ptr<Coin_AutoGen> &getInstance();

	
		Coin_AutoGen();

	
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );
	
		int offset;
	
		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, bool NewOffset );

	
		Vector2 CalcPos( const std::shared_ptr<Bob> &bob, Vector2 BL, Vector2 TR, BobPos pos );

	
		void ActiveFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};

}


#endif	//#ifndef COIN__AUTO
