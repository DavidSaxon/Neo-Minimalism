#include "src/engine/Engine.hpp"

//CONSTRUCTOR
Engine::Engine(SharedDisplay d, SharedSubEngine startState) :
	display(d),
	subEngine(startState),
	running(false),
	frameLength(33),
	accumTime(0)
	{

	entityList = SharedEntityList(new EntityList());

	//seed the random number generator
	srand(time(0));
}

//DESTRUCTOR
Engine::~Engine() {
}

//PUBLIC MEMBER FUNCTIONS
void Engine::init() {

	//create a new resource manager
	resourceManager = SharedResourceManager(new ResourceManager());
	resourceManager->init();

	//TODO: create a new media player

	//create a new camera
	camera = SharedCamera(new Camera());

	//create a new renderer
	renderer = SharedRenderer(new Renderer(entityList, display,
		camera, util::vec::Vector4D(0.0, 0.0, 0.0, 1.0), 500.0));
	renderer->init();

	//initialise the sub engine
	subEngine->init(resourceManager, entityList, camera);

	//TODO: create a new physics engine

	//set the start time
	startTime = SDL_GetTicks();

	//the engine has successfully been initialised
	running = true;
}

void Engine::execute() {

	PhysicsController physics(entityList);

	while (running) {

		//is true when the current state has finished
		bool next = false;

		//find the amount of time past since the last frame
        unsigned long newTime = SDL_GetTicks();
        unsigned frameTime =  newTime - startTime;//- startFrame + accumTime;
        accumTime += frameTime;
        if (accumTime > 66) {

        	accumTime = 66;
        }

        while (accumTime >= frameLength && !next) {

        	if (!subEngine->pause) {

        		physics.update();
    		}

			//execute a cycle of the sub engine
			next = subEngine->execute();

			accumTime -= frameLength;
		}

		startTime = SDL_GetTicks();

		//render
		renderer->render();

    	if (subEngine->pause) {

    		glPushMatrix();

    		glLoadIdentity();

    		resourceManager->getShape("pause")->draw();

    		glPopMatrix();
		}

	    //swap the buffers
    	SDL_GL_SwapBuffers();

		//the current state is complete
		if (next) {

			//check if we should exit
			if (subEngine->shouldExit()) {

				running = false;
			}
			else {

				//go to the next state
				subEngine = subEngine->getNextState();
			}
		}
	}
}