#include "src/states/start_up/StartUp.hpp"

//CONSTRUCTOR
StartUp::StartUp() :
	complete(false),
	loadCounter(0) {

	exit = false;
	pause = false;
	atTitle = false;
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

	camera->getTranslation().setZ(2.2);

    sound = Mix_LoadWAV("res/sound/music/imminent_war.wav");
    if(sound == NULL) {
        fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
    }
     
    musicChannel = Mix_PlayChannel(-1, sound, -1);
    if(musicChannel == -1) {
        fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
    }
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

	//std::cout << complete << std::endl;

	return complete;
}

//PRIVATE MEMBER FUNCTIONS
void StartUp::load() {

	//first stage of loading
	if (loadCounter == 0) {

		//load resources used by all
		resourceManager->loadTextures(res::ALL);
		resourceManager->loadShapes(res::ALL);

		//load the textures needed for start up
		resourceManager->loadTextures(res::START_UP);
		//load the shapes needed for start up
		resourceManager->loadShapes(res::START_UP);
	}
	else if (loadCounter == 1) {

		//remove the omicron splash
		entityList->removeEntity(splash);

			resourceManager->loadTextures(res::LEVEL);
		resourceManager->loadShapes(res::LEVEL);

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

		//load all level resources

		//create the ludum dare splash
		splash = SharedSplash(new Splash(
			resourceManager->getShape("ludum_dare_splash"),
			resourceManager->getShape("splash_fader")));
		entityList->addEntity(boost::dynamic_pointer_cast<Entity>(splash));
	}
	else if (loadCounter == 3) {

		//remove the ludum dare splash
		entityList->removeEntity(splash);

		splash = SharedSplash(new Splash(
			resourceManager->getShape("title"),
			resourceManager->getShape("splash_fader")));
		entityList->addEntity(boost::dynamic_pointer_cast<Entity>(splash));

		atTitle = true;
	}
	else {

		return;
	}

	//increment the load counter
	++loadCounter;
}