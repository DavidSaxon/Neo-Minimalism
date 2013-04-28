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
    torpedoTime(false),
    turnDir(0),
    torP(0),
    lasorFireRate(6),
    lasorCounter(0),
    torFireRate(10),
    torCounter(0) {

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
    entityList->addEntity(SharedEntity(
        new Asteroid(resourceManager->getShape("asteroid_1"),
        util::vec::Vector3D(5.0, 0.0, -20.0))));
    entityList->addEntity(SharedEntity(
        new Asteroid(resourceManager->getShape("asteroid_1"),
        util::vec::Vector3D(6.0, 0.0, -10.0))));
    entityList->addEntity(SharedEntity(
        new Asteroid(resourceManager->getShape("asteroid_1"),
        util::vec::Vector3D(-4.0, 0.0, -8.0))));
    }

bool Level::execute() {

    //poll events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        onEvent(&event);
    }

    //move the player
    if (turnDir == 1) {

        player->turnLeft();
    }
    else if (turnDir == 2) {

        player->turnRight();
    }
    else {

        player->noTurn();
    }

    //set the position of the space box to the player position
    space->setPos(player->getPos());

    //apply camera movement
    camera->setPostRotation(player->getRot());
    camera->setTranslation(player->getPos());
    

    //check for lasor firing
    if (spaceKey) {

        fire();
    }

    update();

    return complete;
}

//PRIVATE MEMBER FUNCTIONS
void Level::update() {

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
}

void Level::fire() {

    if (lasorCounter == 0) {

        util::vec::Vector3D lasorPos;

        if (fireLeft) {

            lasorPos.setX(-0.5);
        }
        else {

            lasorPos.setX(0.5);
        }

        lasorPos += player->getPos();

        fireLeft = !fireLeft;

        entityList->addEntity(SharedEntity(
                new PlayerLasor(resourceManager->getShape("player_lasor"),
                lasorPos)));
    }

    lasorCounter = (lasorCounter + 1) % lasorFireRate;

    if (torCounter == 0) {

        if (torpedoTime) {

            util::vec::Vector3D torPos;

            if (torP == 0) {

                torPos.setX(-0.5);
                torPos.setY(-0.5);
            }
            else if (torP == 1) {

                torPos.setX(0.5);
                torPos.setY(0.5);
            }
            else if (torP == 2) {

                torPos.setX(0.5);
                torPos.setY(-0.5);
            }
            else {

                torPos.setX(-0.5);
                torPos.setY(0.5);
            }

            torPos += player->getPos();

            torP = (torP + 1) % 4;

            entityList->addEntity(SharedEntity(
                new PlayerTorpedo(resourceManager->getShape("player_torpedo"),
                player->getRot(), torPos)));
        }
    }

    torCounter = (torCounter + 1) % torFireRate;
}