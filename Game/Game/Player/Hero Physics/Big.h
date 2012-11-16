﻿#ifndef BIG
#define BIG

#include <global_header.h>

namespace CloudberryKingdom
{
	class BobPhsx;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class BobPhsxBig : public BobPhsxNormal
	{
	public:
		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );

		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxBig> instance;
	public:
		const static std::shared_ptr<BobPhsxBig> &getInstance() const;

		// Instancable class
		BobPhsxBig();
	};
}


#endif	//#ifndef BIG
