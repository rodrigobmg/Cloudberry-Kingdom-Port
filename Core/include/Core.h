#ifndef _CORE_H_
#define _CORE_H_

#include "Architecture/Singleton.h"
#include "ForwardDeclarations.h"

/**
 * The alpha and the omega.
 */
class Core : public Singleton< Core >
{
	/// Is the game currently running?
	bool running_;

	/// The game.
	GameLoop &game_;

private:

	/// No copying.
	Core( const Core & );

	/// No assignment.
	Core &operator = ( const Core & );

public:
	Core( GameLoop &game );
	~Core();

	/// Run application.
	/**
	 * @return 1 on success and 0 on failure.
	 */
	int Run();

	/// Exit application.
	void Exit();

	/// Get core singleton.
	static Core &GetSingleton();

};

/// The core! 
#define CORE Core::GetSingleton()

#endif