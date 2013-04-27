#include "src/states/level/Level.hpp"

//CONSTRUCTOR
Level::Level() :
    complete(false) {

    exit = false;
}

//DESTRUCTOR
Level::~Level() {
}

//PUBLIC MEMBER FUNCTIONS
void Level::init(SharedResourceManager rm,
    SharedEntityList el, SharedCamera cam) {

    //set variables
    resourceManager = rm;
    entityList = el;
    camera = cam;
}

bool Level::execute() {

    //poll events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        onEvent(&event);
    }
    
    return complete;
}