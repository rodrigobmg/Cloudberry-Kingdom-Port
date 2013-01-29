#ifndef RUMBLE
#define RUMBLE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct Rumble : public GUI_Panel
	{
	
		virtual ~Rumble() { }

		Rumble();
		boost::shared_ptr<Rumble> Rumble_Construct();
	
		virtual void ReleaseBody();

		virtual void MyPhsxStep();

	};

}


#endif	//#ifndef RUMBLE
