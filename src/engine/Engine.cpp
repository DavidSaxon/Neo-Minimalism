#include "src/engine/Engine.hpp"

//CONSTRUCTOR
Engine::Engine(SharedDisplay d, SharedSubEngine startState) :
	display(d),
	subEngine(startState),
	running(false),
	frameTime(17),
	accumTime(0)
	{

	entityList = SharedEntityList(new EntityList());
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
		camera, util::vec::Vector4D(0.0, 0.0, 0.0, 1.0), 200.0));
	renderer->init();

	//initialise the sub engine
	subEngine->init(resourceManager, entityList, camera);

	//TODO: create a new physics engine

	//set the start time
	startFrame = SDL_GetTicks();

	//the engine has successfully been initialised
	running = true;
}

void Engine::execute() {

	while (running) {

		//is true when the current state has finished
		bool next = false;

		//find the amount of time past since the last frame
        long currentTime = SDL_GetTicks() - startFrame + accumTime;

        while (currentTime >= frameTime && !next) {

			//execute a cycle of the sub engine
			next = subEngine->execute();

			currentTime -= frameTime;
		}

		accumTime = currentTime;
		startFrame = SDL_GetTicks();

		//render
		renderer->render();

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