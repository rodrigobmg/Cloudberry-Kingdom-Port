﻿#include "PhsxData.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	PhsxData::PhsxData( float pos_x, float pos_y, float vel_x, float vel_y, float acc_x, float acc_y )
	{
		Position = Vector2( pos_x, pos_y );
		Velocity = Vector2( vel_x, vel_y );
		Acceleration = Vector2( acc_x, acc_y );
	}

	void PhsxData::UpdatePosition()
	{
		Position += Velocity;
	}

	void PhsxData::Integrate()
	{
		Velocity += Acceleration;
		Position += Velocity;
	}
}