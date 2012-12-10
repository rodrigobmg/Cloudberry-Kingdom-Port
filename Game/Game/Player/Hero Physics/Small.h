﻿#ifndef SMALL
#define SMALL

#include <global_header.h>

namespace CloudberryKingdom
{
	class BobPhsxSmall : public BobPhsxNormal
	{

	public:
		static void InitializeStatics();

	public:
		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );
		void Set( const std::shared_ptr<BobPhsx> &phsx, Vector2 modsize );

		// Singleton
	protected:
		virtual void InitSingleton();
	public:
		static std::shared_ptr<BobPhsxSmall> instance;
	public:
		const static std::shared_ptr<BobPhsxSmall> &getInstance();

		// Instancable class
		BobPhsxSmall();
	};
}


#endif	//#ifndef SMALL
