/**************************************************************\
| The start up which is used for loading initial resources and |
| displaying splash screens.								   |
|															   |
| @author David Saxon										   |
\**************************************************************/

#ifndef OMICRON_STATES_STARTUP_STARTUP_H_
#	define OMICRON_STATES_STARTUP_STARTUP_H_

#include <iostream>

#include "src/Utilities/MacroUtil.hpp"

#include "src/entities/start_up/Splash.hpp"
#include "src/states/level/Level.hpp"
#include "src/sub_engine/SubEngine.hpp"

//TYPEDEF
typedef boost::shared_ptr<Splash> SharedSplash;

class StartUp : public SubEngine {
public:

	//CONSTRUCTOR
	/*!Creates a new start up sub engine*/
	StartUp();

	//DESTRUCTOR
	/*!Destroys the start up engine*/
	~StartUp();

	//PUBLIC MEMBER FUNCTIONS
	/*!Initialises the start up engine
	@rm the resource manager
	@el the entity list
	@cam the camera for th sub engine to use*/
	void init(SharedResourceManager rm,
		SharedEntityList el, SharedCamera cam);

	/*!Executes a cycle of the start up engine
	@return true once execution has finished*/
	bool execute();

private:

	//VARIABLES
	//is true until execution is complete
	bool complete;
	//counts the stages of loading
	unsigned loadCounter;

	//the splash screen
	SharedSplash splash;

	//CONSTRUCTOR
	DISALLOW_COPY_AND_ASSIGN(StartUp);

	//PRIVATE MEMBER FUNCTIONS
	/*!Loads the needed resources in stages*/
	void load();

//EVENT
private:

	/*!When a key is pressed*/
    void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
};

#endif