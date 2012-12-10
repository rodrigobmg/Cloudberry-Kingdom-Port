﻿#ifndef LAMBDAFUNC_1
#define LAMBDAFUNC_1

namespace CloudberryKingdom
{
	template<typename T, typename OutputType>
	struct LambdaFunc_1
	{
	
		virtual OutputType Apply( const T &t ) = 0;
	};
}


#endif	//#ifndef LAMBDAFUNC_1
