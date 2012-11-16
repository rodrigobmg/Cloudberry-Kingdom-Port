﻿#ifndef MAKEFINALDOOR
#define MAKEFINALDOOR

#include "../Game/Level/Make/MakePiece/MakeThing.h"
#include "../Core/Lambdas/LambdaFunc_1.h"
#include <cmath>

namespace CloudberryKingdom
{
	class BlockBase;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class Door;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class MakeFinalDoorVertical : public MakeThing
	{
	private:
		class ElementPositionProjectY : public LambdaFunc_1<BlockBase*, float>
		{
		public:
			float Apply( const std::shared_ptr<BlockBase> &element );
		};

	private:
		class MatchUsedLambda : public LambdaFunc_1<BlockBase*, bool>
		{
		public:
			MatchUsedLambda();

			bool Apply( const std::shared_ptr<BlockBase> &match );
		};

	protected:
		std::shared_ptr<Level> MyLevel;

		/// <summary>
		/// The block on which the final door rests on.
		/// </summary>
	private:
		std::shared_ptr<BlockBase> FinalBlock;

		/// <summary>
		/// The position of the final door.
		/// </summary>
		Vector2 FinalPos;

	public:
		MakeFinalDoorVertical( const std::shared_ptr<Level> &level );

		virtual void Phase1();

		virtual void Phase2();

	protected:
		std::shared_ptr<Door> MadeDoor;
	public:
		virtual void Phase3();

		virtual void Cleanup();
	};
}


#endif	//#ifndef MAKEFINALDOOR