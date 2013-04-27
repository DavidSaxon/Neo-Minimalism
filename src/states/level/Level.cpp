#include "src/states/level/Level.hpp"

//CONSTRUCTOR
Level::Level() :
    complete(false),
    upKey(false),
    downKey(false),
    leftKey(false),
    rightKey(false),
    spaceKey(false),
    fireLeft(false),
    lasorSpeed(0.5),
    torpedoTime(false) {

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
    player = SharedPlayer(new Player(resourceManager->getShape("cockpit"),
        resourceManager->getShape("cross_hair")));
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

    //check for lasor firing
    if (spaceKey) {

        util::vec::Vector3D lasorPos;

        if (fireLeft) {

            lasorPos.setX(-0.5);
        }
        else {

            lasorPos.setX(0.5);
        }

        lasorPos += player->getPos();

        //short hand rotations
        util::vec::Vector3D playerRot = player->getTurnRot();
        float x = playerRot.getX() * util::val::degreesToRadians;
        float y = playerRot.getY() * util::val::degreesToRadians;
        float z = playerRot.getZ() * util::val::degreesToRadians;

        float rotMatrix[] = {cos(y)*cos(z), sin(x)*sin(y)*cos(z)-cos(x)*sin(z),
            sin(x)*sin(z)+cos(x)*sin(y)*cos(z),
            cos(y)*sin(z), cos(x)*cos(z)+sin(x)*sin(y)*sin(z),
            cos(x)*sin(y)*sin(z)-sin(x)*cos(z),
            -sin(y), sin(x)*cos(y), cos(x)*cos(y)};

        util::vec::Vector3D lasorMoveSpeed(lasorSpeed * rotMatrix[2],
            lasorSpeed * rotMatrix[5], -(lasorSpeed * rotMatrix[8]));

        fireLeft = !fireLeft;
        spaceKey = false;

        if (!torpedoTime) {

            entityList->addEntity(SharedEntity(
                new PlayerLasor(resourceManager->getShape("player_lasor"),
                player->getTurnRot(), lasorPos,
                lasorMoveSpeed)));
        }
        else {

            entityList->addEntity(SharedEntity(
                new PlayerTorpedo(resourceManager->getShape("player_torpedo"),
                player->getTurnRot(), lasorPos,
                lasorMoveSpeed)));
        }
    }

    EList newEntities;
    EList removeEntities;

    //update the entities
    EList::iterator
        it = entityList->getEntities().begin(),
        ite = entityList->getEntities().end();
    for (; it != ite; ++it) {

        if ((*it)->shouldRemove) {

            removeEntities.push_back(*it);
        }
        else {

            (*it)->update();

            if ((*it)->hasNew) {

                EList nel = (*it)->getNew(resourceManager);

                for (unsigned i = 0; i < nel.size(); ++i) {

                    newEntities.push_back(nel[i]);
                }
            }
        }
    }

    //add the new entities
    for (unsigned i = 0; i < newEntities.size(); ++i) {

        entityList->addEntity(newEntities[i]);
    }

    //remove the dead entities
    for (unsigned i = 0; i < removeEntities.size(); ++i) {

        entityList->removeEntity(removeEntities[i]);
    }

    return complete;
}