/****************************************************************\
| The main engine of omicron, controlls the current sub engines, |
| entity list, event input, and the main loop.								 |
|															     |
| @author David Saxon									         |
\****************************************************************/

#ifndef OMICRON_ENGINE_ENGINE_H_
#	define OMICRON_ENGINE_ENGINE_H_

#include <boost/shared_ptr.hpp>
#include <iostream>

#include "src/Utilities/MacroUtil.hpp"

#include "src/display/DisplaySurface.hpp"
#include "src/renderer/Renderer.hpp"
#include "src/resource/ResourceManager.hpp"
#include "src/sub_engine/SubEngine.hpp"

//TYPEDEFS
typedef boost::shared_ptr<DisplaySurface> SharedDisplay;
typedef boost::shared_ptr<Renderer> SharedRenderer;
typedef boost::shared_ptr<Camera> SharedCamera;
typedef boost::shared_ptr<ResourceManager> SharedResourceManager;

class Engine {
public:

	//CONSTRUCTOR
	/*!Creates a new engine
	@d the display window to use
	@startState the starting sub engine*/
	Engine(SharedDisplay d, SharedSubEngine startState);

	//DESTRUCTOR
	/*!Destroys this engine*/
	~Engine();

	//PUBLIC MEMBER FUNCTIONS
	/*!Initialises the engine*/
	void init();

	/*!executes the engine*/
	void execute();

private:

	//CONSTRUCTOR
	DISALLOW_COPY_AND_ASSIGN(Engine);

	//VARIBLES
	//is true while the engine is running
	bool running;
	//the entity list
	SharedEntityList entityList;
	//the display window
	SharedDisplay display;
	//the current sub engine
	SharedSubEngine subEngine;
	//the current renderer
	SharedRenderer renderer;
	//the camera
	SharedCamera camera;
	//the resource manager
	SharedResourceManager resourceManager;

	//fps management
	//the time of a frame in milliseconds
	unsigned frameTime;
	//the time the frame start
	float startFrame;
	//the accumulated time since the last frame
	float accumTime;

	//TODO: physics controller
	//TODO: media controller
};

#endif