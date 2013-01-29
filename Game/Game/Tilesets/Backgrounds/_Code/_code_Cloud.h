﻿#ifndef _CODE_CLOUD
#define _CODE_CLOUD

#include <global_header.h>

namespace CloudberryKingdom
{

	struct Background_Cloud : public BackgroundTemplate
	{

		virtual ~Background_Cloud() { }

		Background_Cloud( const std::wstring &Name );

		virtual void Code( const boost::shared_ptr<Background> &b );

	};

	struct Background_CloudRain : public BackgroundTemplate
	{
	
		virtual ~Background_CloudRain() { }

		Background_CloudRain( const std::wstring &Name );

		virtual void Code( const boost::shared_ptr<Background> &b );

	};

}



#endif	//#ifndef _CODE_CLOUD
