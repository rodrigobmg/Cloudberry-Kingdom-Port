﻿#ifndef _CODE_FOREST
#define _CODE_FOREST

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Background_Forest : public BackgroundTemplate
	{

		virtual ~Background_Forest() { }

		Background_Forest( const std::wstring &Name );

		virtual void Code( const boost::shared_ptr<Background> &b );

	};

	struct Background_ForestSnow : public BackgroundTemplate
	{
	
		virtual ~Background_ForestSnow() { }

		Background_ForestSnow( const std::wstring &Name );

		virtual void Code( const boost::shared_ptr<Background> &b );

	};

}


#endif	//#ifndef _CODE_FOREST
