#ifndef SPIKEYLINE__AUTO
#define SPIKEYLINE__AUTO

#include <small_header.h>

//#include "Game/Objects/ObjectBase.h"
//#include "Game/Level/Make/DifficultyHelper.h"
//#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/SpikeyLine.h"
//#include "Game/Tools/Recycler.h"


namespace CloudberryKingdom
{

	struct SpikeyLine_Parameters : public AutoGen_Parameters
	{
	
		virtual ~SpikeyLine_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "SpikeyLine_Parameters" );
#endif
		}


		struct _Special
		{
		};
	
		Param LineStep, LinePeriod;
		bool Make;

		_Special Special;

		//public List<List<SpikeyLine> > Lines = new List<List<SpikeyLine>>();

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );
	
	};

	struct SpikeyLine_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<SpikeyLine_AutoGen> instance;
	
		const static boost::shared_ptr<SpikeyLine_AutoGen> &getInstance();

	
		SpikeyLine_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void CreateLine( const boost::shared_ptr<Level> &level, Vector2 pos );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef SPIKEYLINE__AUTO
