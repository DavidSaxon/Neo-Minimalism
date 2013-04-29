/***********************************\
| State representing standard level |
|                                   |
| @author David Saxon               |
\***********************************/

#ifndef NEOMINIMALISM_STATES_LEVEL_H_
#   define NEOMINIMALISM_STATES_LEVEL_H_

#include <SDL/SDL_mixer.h>
#include <fstream>

#include "src/Utilities/MacroUtil.hpp"

#include "src/entities/level/back_ground/BelowPlanet.hpp"
#include "src/entities/level/back_ground/SpaceBox.hpp"
#include "src/entities/level/enviroment/Asteroid.hpp"
#include "src/entities/level/enemy/Flyer.hpp"
#include "src/entities/level/enemy/Interceptor.hpp"
#include "src/entities/level/enemy/Station.hpp"
#include "src/entities/level/enemy/Drone.hpp"
#include "src/entities/level/enemy/Boss.hpp"
#include "src/entities/level/enviroment/Wall.hpp"
#include "src/entities/level/player/Player.hpp"
#include "src/entities/level/weapons/PlayerLasor.hpp"
#include "src/entities/level/weapons/PlayerTorpedo.hpp"
#include "src/sub_engine/SubEngine.hpp"

//TYPEDEF
typedef boost::shared_ptr<Player> SharedPlayer;
typedef boost::shared_ptr<Boss> SharedBoss;
typedef boost::shared_ptr<SpaceBox> SharedSpaceBox;
typedef boost::shared_ptr<BelowPlanet> SharedBelowPlanet;

class Level : public SubEngine {
public:

    //CONSTRUCTOR
    Level();

    //DESTRUCTOR
    ~Level();

    //PUBLIC MEMBER FUNCTIONS
    /*!Initialises the engine*/
    void init(SharedResourceManager rm,
        SharedEntityList el, SharedCamera cam);

    /*!Executes the engine*/
    bool execute();

private:

    //VARIABLES
    //returns true once the level has finsihed execution
    bool complete;

    //the player
    SharedPlayer player;
    //the space box
    SharedSpaceBox space;
    SharedBelowPlanet planet;
    SharedBoss boss;

    //keys
    bool upKey;
    bool downKey;
    bool leftKey;
    bool rightKey;
    bool spaceKey;

    unsigned turnDir;
    bool fireLeft;
    unsigned torP;
    float lasorSpeed;
    unsigned lasorFireRate;
    unsigned lasorCounter;
    unsigned torFireRate;
    unsigned torCounter;
    
    Mix_Chunk* music;

    Mix_Chunk* lasorFireFx;
    int lasorChannel;

    Mix_Chunk* torpedoFireFx;
    int torpedoChannel;

    Mix_Chunk* explosion_1;

    Mix_Chunk* explosion_2;

    Mix_Chunk* damageLasor;

    Mix_Chunk* damageTorpedo;

    int deadTime;
    int deadCounter;
    bool restarting;

    util::vec::Vector3D dPos;
    util::vec::Vector3D dRot;

    bool bossRestart;
    int bossCounter;

    unsigned stage;

    bool bossFight;

    std::vector<std::vector<char> > level;

    int lastZ;

    //CONSTRUCTOR
    DISALLOW_COPY_AND_ASSIGN(Level);

    //PRIVATE MEMBER FUNCTIONS
    void update();

    void fire();

    void create();

    void buildLevel(std::string filename);

//EVENT
private:

    /*!When a key is pressed*/
    void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

    /*!When a key is released*/
    void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
};


#endif