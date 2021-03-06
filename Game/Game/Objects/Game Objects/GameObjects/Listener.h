#ifndef LISTENER
#define LISTENER

#include <small_header.h>

//#include "Core/Input/ButtonCheck.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"


namespace CloudberryKingdom
{

	struct Listener : public GUI_Panel
	{

		virtual ~Listener()
		{
#ifdef BOOST_BIN
			OnDestructor( "Listener" );
#endif
		}


		void ReleaseBody();

		enum Type
		{
			Type_ON_DOWN,
			Type_ON_PRESSED
		};
	
		Listener();
		boost::shared_ptr<Listener> Listener_Construct();
		Listener( ControllerButtons button, const boost::shared_ptr<Lambda> &action );
		boost::shared_ptr<Listener> Listener_Construct( ControllerButtons button, const boost::shared_ptr<Lambda> &action );

		Type MyType;

		boost::shared_ptr<Lambda> MyAction;
		int TriggeringPlayerIndex;

		/// <summary>
		/// If true the listener is removed immediately after it activates
		/// </summary>
		bool RemoveAfterActivation;

		virtual void Activate();

		ControllerButtons MyButton;
		boost::shared_ptr<ButtonClass> MyButton2;
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef LISTENER
