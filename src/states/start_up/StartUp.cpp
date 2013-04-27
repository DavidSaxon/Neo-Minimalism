#include "src/states/start_up/StartUp.hpp"

//CONSTRUCTOR
StartUp::StartUp() :
	complete(false),
	loadCounter(0) {
}

//DESTRUCTOR
StartUp::~StartUp() {
}

//PUBLIC MEMBER FUNCTIONS
void StartUp::init(SharedResourceManager rm,
	SharedEntityList el, SharedCamera cam) {

	//set variables
	resourceManager = rm;
	entityList = el;
	camera = cam;

	//perform the first stage of loading
	load();

	//create the omicron splash image
	splash = SharedSplash(new Splash(
		resourceManager->getShape("omicron_splash"),
		resourceManager->getShape("splash_fader")));
	entityList->addEntity(boost::dynamic_pointer_cast<Entity>(splash));

	camera->getTranslation().setZ(-2.2);
}

bool StartUp::execute() {

	//poll events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

    	onEvent(&event);
	}

	//check if the current splash has finished fading
	if (splash->fadeComplete()) {

		load();
	}

	//update the entities
	EList::iterator
		it = entityList->getEntities().begin(),
		ite = entityList->getEntities().end();
	for (; it != ite; ++it) {

		(*it)->update();
	}

	return complete;
}

//PRIVATE MEMBER FUNCTIONS
void StartUp::load() {

	//first stage of loading
	if (loadCounter == 0) {

		//load the textures needed for start up
		resourceManager->loadTextures(res::START_UP);
		//load the shapes needed for start up
		resourceManager->loadShapes(res::START_UP);
	}
	else if (loadCounter == 1) {

		//remove the omicron splash
		entityList->removeEntity(splash);

		//free the omicron resources
		//TODO:

		//create the made for splash
		splash = SharedSplash(new Splash(
			resourceManager->getShape("made_for_splash"),
			resourceManager->getShape("splash_fader")));
		entityList->addEntity(boost::dynamic_pointer_cast<Entity>(splash));

	}
	else if (loadCounter == 2) {

		//remove the made for splash
		entityList->removeEntity(splash);

		//create the ludum dare splash
		splash = SharedSplash(new Splash(
			resourceManager->getShape("ludum_dare_splash"),
			resourceManager->getShape("splash_fader")));
		entityList->addEntity(boost::dynamic_pointer_cast<Entity>(splash));
	}
	else if (loadCounter == 3) {

		//remove the ludum dare splash
		entityList->removeEntity(splash);

		//TODO: free the start up resources

		//set the next state
		nextState = SharedSubEngine(new StartUp);
		nextState->init(resourceManager, entityList, camera);

		//execution is complete
		complete = true;
	}

	//increment the load counter
	++loadCounter;
}