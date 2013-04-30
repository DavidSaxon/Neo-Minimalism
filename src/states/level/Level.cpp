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
    turnDir(0),
    torP(0),
    lasorFireRate(6),
    lasorCounter(0),
    torFireRate(10),
    torCounter(0),
    deadTime(60),
    deadCounter(0),
    restarting(false),
    lastZ(0),
    stage(0),
    bossFight(false){

    pause = false;
    exit = false;
    lasorChannel = 5;

    bossRestart = false;
    bossCounter = 0;
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
    camera->setTranslation(util::vec::Vector3D(0.0, 0.0, 0.0));

    create();

    int musicChannel = -1;

    lasorChannel = -1;
    torpedoChannel = -1;

    //pload sounds
    music = Mix_LoadWAV("res/sound/music/path_of_the_totalist.wav");
    lasorFireFx = Mix_LoadWAV("res/sound/fx/lasor_fire.wav");
    torpedoFireFx = Mix_LoadWAV("res/sound/fx/torpedo_fire.wav");
    explosion_1 = Mix_LoadWAV("res/sound/fx/explosion_1.wav");
    explosion_2 = Mix_LoadWAV("res/sound/fx/boss_die.wav");
     
    musicChannel = Mix_PlayChannel(-1, music, -1);
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

    if (!restarting) {

        //set the position of the space box to the player position
        space->setPos(player->getPos());
        planet->setPos(player->getPos());

        //apply camera movement
        camera->setPostRotation(player->getRot());
        camera->setTranslation(player->getPos());

    }
    else {

        camera->setPostRotation(dRot);
        camera->setTranslation(dPos);
    }
    

    //check for lasor firing
    if (spaceKey) {

        fire();
    }

    update();

    if (restarting) {

        if (deadCounter == 0) {

            create();
        }
        else {

            --deadCounter;
        }
    }

    return complete;
}

//PRIVATE MEMBER FUNCTIONS
void Level::update() {

    if (!pause) {

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

                if ((*it)->getPos().getZ() > player->getPos().getZ() + 0.5) {

                    (*it)->shouldRemove = true;
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

        //read a line of the level
        if (-static_cast<int>(player->getPos().getZ()) > lastZ) {

            //add entities from the level

            if (lastZ < level.size()) {

                for (int i = 0; i < level[lastZ].size(); ++i) {

                    float jitter = (rand() % 100) / 100.0;

                    if (level[lastZ][i] == 'A') {

                        entityList->addEntity(SharedEntity(
                            new Asteroid(resourceManager->getShape("asteroid_1"),
                            util::vec::Vector3D((i * 2) - 14 + jitter, 0.0, -(lastZ + 100)))));
                    }
                    else if (level[lastZ][i] == 'F') {

                        entityList->addEntity(SharedEntity(
                            new Flyer(resourceManager->getShape("enemy_flyer"),
                            resourceManager->getShape("flyer_window"),
                            util::vec::Vector3D((i * 2) - 14 + jitter, 0.0, -(lastZ + 100)))));
                    }
                    else if (level[lastZ][i] == 'I') {

                        entityList->addEntity(SharedEntity(
                            new Interceptor(resourceManager->getShape("interceptor"),
                            resourceManager->getShape("interceptor_window"),
                            util::vec::Vector3D((i * 2) - 14 + jitter, 0.0, -(lastZ + 100)))));
                    }
                    else if (level[lastZ][i] == 'S') {

                        entityList->addEntity(SharedEntity(
                            new Station(resourceManager->getShape("station"),
                            util::vec::Vector3D((i * 2) - 14 + jitter, 0.0, -(lastZ + 100)))));
                    }
                    else if (level[lastZ][i] == 'D') {

                        entityList->addEntity(SharedEntity(
                            new Drone(resourceManager->getShape("drone"),
                            util::vec::Vector3D((i * 2) - 14 + jitter, 0.0, -(lastZ + 100)))));
                    }
                }
            }
            else {

                if (!bossFight) {

                    stage = (stage + 1) % 3;
                    create();
                }
            }

            //add walls
            if (lastZ % 2 == 0) {

                {

                unsigned wrc = rand() % 10;
                std::string wallTag("wall_1");

                if (wrc == 9) {

                    wallTag = "wall_4";
                }
                else if (wrc == 8) {

                    wallTag = "wall_3";
                }
                else if (wrc == 7) {

                    wallTag = "wall_4";
                }

                entityList->addEntity(SharedEntity(
                    new Wall(resourceManager->getShape(wallTag),
                    util::vec::Vector3D(16.0, 0.0, -(lastZ + 200)))));
                }
                {

                unsigned wrc = rand() % 10;
                std::string wallTag("wall_1");

                if (wrc == 9) {

                    wallTag = "wall_4";
                }
                else if (wrc == 8) {

                    wallTag = "wall_3";
                }
                else if (wrc == 7) {

                    wallTag = "wall_4";
                }

                entityList->addEntity(SharedEntity(
                    new Wall(resourceManager->getShape(wallTag),
                    util::vec::Vector3D(-16.0, 0.0, -(lastZ + 200)))));
                }
            }

            ++lastZ;
        }

        if (bossFight) {

            if (boss->health <= 0 && !bossRestart) {

                bossRestart = true;
                bossCounter = 40;
                Mix_PlayChannel(-1, explosion_2, 0);
            }
        }

        if (bossRestart) {

            if (bossCounter == 0) {

                stage = 0;
                bossRestart = false;
                bossCounter = 0;
                bossFight = false;
                create();
            }
            else {

                --bossCounter;
            }
        }

        if (player->dead && !restarting) {

            Mix_PlayChannel(-1, explosion_2, 0);

            restarting = true;

            deadCounter = deadTime;

            dPos = player->getPos();
            dPos.set(dPos.getX(), dPos.getY(), dPos.getZ() + 5);

            dRot.set(5, 0, 0);

            util::vec::Vector3D ePos = player->getPos();
            ePos.setZ(ePos.getZ() + 0.5);

            entityList->addEntity(SharedEntity(
                new Explosion(resourceManager->getShape("player_explosion"),
                ePos, 0.2, 50, true)));

        }
    }
}

void Level::fire() {

    if (lasorCounter == 0) {

        util::vec::Vector3D lasorPos;

        if (fireLeft) {

            lasorPos.setX(-0.25);
        }
        else {

            lasorPos.setX(0.25);
        }

        lasorPos += player->getPos();

        fireLeft = !fireLeft;

        if (lasorChannel == -1) {

            lasorChannel = Mix_PlayChannel(-1, lasorFireFx, 1);
        }
        else {

            Mix_PlayChannel(lasorChannel, lasorFireFx, 1);
        }

        entityList->addEntity(SharedEntity(
                new PlayerLasor(resourceManager->getShape("player_lasor"),
                lasorPos)));
    }

    lasorCounter = (lasorCounter + 1) % lasorFireRate;

    if (torCounter == 0) {

        bool up = false;

        if (player->torpedo) {

            util::vec::Vector3D torPos;

            if (torP == 0) {

                torPos.setX(-0.25);
                torPos.setY(-0.25);
            }
            else if (torP == 1) {

                torPos.setX(0.25);
                torPos.setY(0.25);

                up = true;
            }
            else if (torP == 2) {

                torPos.setX(0.25);
                torPos.setY(-0.25);
            }
            else {

                torPos.setX(-0.25);
                torPos.setY(0.25);

                up = true;
            }

            torPos += player->getPos();

            torP = (torP + 1) % 4;

            if (lasorChannel == -1) {

                lasorChannel = Mix_PlayChannel(-1, torpedoFireFx, 1);
            }
            else {

                Mix_PlayChannel(lasorChannel, torpedoFireFx, 1);
            }

            entityList->addEntity(SharedEntity(
                new PlayerTorpedo(resourceManager->getShape("player_torpedo"),
                player->getRot(), torPos, up)));
        }
    }

    torCounter = (torCounter + 1) % torFireRate;
}

void Level::create() {

    restarting = false;

    entityList->clear();

    level.clear();

    lastZ = 0;

    //create the entities
    player = SharedPlayer(new Player(resourceManager->getShape("cockpit"),
        resourceManager->getShape("cross_hair"),
        resourceManager->getShape("level_fader")));
    entityList->addEntity(boost::dynamic_pointer_cast<Entity>(player));

    space = SharedSpaceBox(new SpaceBox(
        resourceManager->getShape("space_box")));
    entityList->addEntity(boost::dynamic_pointer_cast<Entity>(space));

    planet = SharedBelowPlanet(new BelowPlanet(resourceManager->getShape("planet_1"),
            resourceManager->getShape("sun"),
            resourceManager->getShape("wall_end")));
    entityList->addEntity(boost::dynamic_pointer_cast<Entity>(planet));

    //add walls
    for (int i = 0; i < 100; ++i) {

        unsigned wrc = rand() % 10;
        std::string wallTag("wall_1");

        if (wrc == 9) {

            wallTag = "wall_4";
        }
        else if (wrc == 8) {

            wallTag = "wall_3";
        }
        else if (wrc == 7) {

            wallTag = "wall_4";
        }

        entityList->addEntity(SharedEntity(
            new Wall(resourceManager->getShape(wallTag),
            util::vec::Vector3D(16.0, 0.0, -i * 2))));
    }
    for (int i = 0; i < 100; ++i) {

        unsigned wrc = rand() % 10;
        std::string wallTag("wall_1");

        if (wrc == 9) {

            wallTag = "wall_4";
        }
        else if (wrc == 8) {

            wallTag = "wall_3";
        }
        else if (wrc == 7) {

            wallTag = "wall_4";
        }

        entityList->addEntity(SharedEntity(
            new Wall(resourceManager->getShape(wallTag),
            util::vec::Vector3D(-16.0, 0.0, -i * 2))));
    }

    if (stage == 1) {

        buildLevel("res/levels/hard.lvl");
    }
    else if (stage == 2) {

        bossFight =  true;

        boss = SharedBoss(new Boss(resourceManager->getShape("boss_body"),
            resourceManager->getShape("boss_arms")));
        entityList->addEntity(boost::dynamic_pointer_cast<Entity>(boss));
    }
}

void Level::buildLevel(std::string filename) {

    std::ifstream inFile(filename.c_str());

    //iterate over the file
    while (inFile.good()) {

        //buffer for the line
        char lineBuffer[50];

        //get the line
        inFile.getline(lineBuffer, 50);

        //conver to a string
        std::string line(lineBuffer);

        if (line[0] == '0') {

            for (unsigned i = 0; i < 100; ++i) {

                std::vector<char> blank;

                level.push_back(blank);
            }
        }
        else if (line[0] == '1') {

            for (unsigned i = 0; i < 10; ++i) {

                std::vector<char> blank;

                level.push_back(blank);
            }
        }
        else if (line[0] == '2') {

            for (unsigned i = 0; i < 50; ++i) {

                std::vector<char> blank;

                level.push_back(blank);
            }
        }
        else if (line[0] == '5') {

            for (unsigned i = 0; i < 5; ++i) {

                std::vector<char> blank;

                level.push_back(blank);
            }
        }
        else if (line[0] != 0) {

            std::vector<char> levelLine;

            for (int i = 0; i < 14; ++i) {

                levelLine.push_back(line[i * 2]);
            }

            level.push_back(levelLine);
        }
    }
}
