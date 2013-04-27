#include "src/states/level/Level.hpp"

//CONSTRUCTOR
Level::Level() :
    complete(false),
    upKey(false),
    downKey(false),
    leftKey(false),
    rightKey(false) {

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

    //create the entities
    player = SharedPlayer(new Player(resourceManager->getShape("cockpit")));
    entityList->addEntity(boost::dynamic_pointer_cast<Entity>(player));

    space = SharedSpaceBox(new SpaceBox(
        resourceManager->getShape("space_box")));
    entityList->addEntity(boost::dynamic_pointer_cast<Entity>(space));

    entityList->addEntity(SharedEntity(
        new Asteroid(resourceManager->getShape("asteroid_1"),
        util::vec::Vector3D(0.0, 0.0, -10.0))));
}

bool Level::execute() {

    //poll events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        onEvent(&event);
    }

    //move the player
    if (upKey) {

        player->turnUp();
    }
    if (downKey) {

        player->turnDown();
    }
    if (leftKey) {

        player->turnLeft();
    }
    if (rightKey) {

        player->turnRight();
    }

    //set the position of the space box to the player position
    space->setPos(player->getPos());

    //apply camera movement
    camera->setTranslation(player->getPos());
    camera->setPostRotation(player->getTurnRot());

    //update the entities
    EList::iterator
        it = entityList->getEntities().begin(),
        ite = entityList->getEntities().end();
    for (; it != ite; ++it) {

        (*it)->update();
    }

    return complete;
}