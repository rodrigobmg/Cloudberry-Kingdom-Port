﻿#ifndef FIRESNAKE__AUTO
#define FIRESNAKE__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Firesnake_Parameters : public AutoGen_Parameters
	{
	
		struct _Special
		{
		};
	
		Param Step, Period;
		VectorParam RadiiX, RadiiY;

		bool Make;

		_Special Special;

		std::vector<std::vector<unsigned long long> > Snakes;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		Firesnake_Parameters() :
			Make( false )
		{
			InitializeInstanceFields();
		}
	};

	struct Firesnake_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<Firesnake_AutoGen> instance;
	
		const static boost::shared_ptr<Firesnake_AutoGen> &getInstance();

	
		Firesnake_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		boost::shared_ptr<Firesnake_Parameters> GetParams( const boost::shared_ptr<Level> &level );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void CreateLine( const boost::shared_ptr<Level> &level, Vector2 pos );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef FIRESNAKE__AUTO
