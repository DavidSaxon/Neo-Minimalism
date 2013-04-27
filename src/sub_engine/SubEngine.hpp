/*********************************************************************\
| Virtual class that is extended by all sub engines in the engine.    |
| provides functions for initialisation, extecution, and event input. |
|																      |
| @author David Saxon												  |
\*********************************************************************/

#ifndef OMICRON_SUBENGINE_SUBENGINE_H_
#	define OMICRON_SUBENGINE_SUBENGINE_H_

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <SDL/SDL.h>

#include "src/camera/Camera.hpp"
#include "src/entity_list/EntityList.hpp"
#include "src/event/Event.hpp"
#include "src/resource/ResourceManager.hpp"	
#include "src/resource/Groups.hpp"

class SubEngine;

//TYPEDEFS
typedef boost::shared_ptr<ResourceManager> SharedResourceManager;
typedef boost::shared_ptr<EntityList> SharedEntityList;
typedef boost::shared_ptr<Camera> SharedCamera;
typedef boost::shared_ptr<SubEngine> SharedSubEngine;

class SubEngine : public Event {
public:

	//DESTRUCTOR
	/*!Destroys the sub engine
	^INL*/
	virtual ~SubEngine() {
	}

	//PUBLIC MEMBER FUNCTIONS
	/*!Initialises the sub engine
	@rm the resource manager
	@el the entity list
	@cam the camera for th sub engine to use*/
	virtual void init(SharedResourceManager rm,
		SharedEntityList el, SharedCamera cam) = 0;

	/*!Exectues the sub engine
	@return true if the sub engine exectution has finished*/
	virtual bool execute() = 0;

	/*!^INL
	@return the next sub engine to use*/
	SharedSubEngine getNextState();

	/*!^INL
	@return true if the application should exit*/
	bool shouldExit() const;

protected:

	//VARIABLES
	//the resource manager
	SharedResourceManager resourceManager;
	//the entityList
	SharedEntityList entityList;
	//the camera to use
	SharedCamera camera;
	//TODO: the media player to use

	//the next sub engine
	SharedSubEngine nextState;

	//PROTECTED MEMBER FUNCTIONS
    /*!Handles events
    ^INL
    @event the current SDL event*/
    void onEvent(SDL_Event* event);
};

//INLINE
//PUBLIC MEMBER FUNCTIONS
inline void SubEngine::onEvent(SDL_Event* event) {

	//pass on the event
    Event::onEvent(event);
}

inline SharedSubEngine SubEngine::getNextState() {

	return nextState;
}

inline bool SubEngine::shouldExit() const {

	return false;
}

#endif