/***********************************\
| State representing standard level |
|                                   |
| @author David Saxon               |
\***********************************/

#ifndef NEOMINIMALISM_STATES_LEVEL_H_
#   define NEOMINIMALISM_STATES_LEVEL_H_

#include "src/Utilities/MacroUtil.hpp"

#include "src/entities/level/back_ground/SpaceBox.hpp"
#include "src/entities/level/enviroment/Asteroid.hpp"
#include "src/entities/level/player/Player.hpp"
#include "src/sub_engine/SubEngine.hpp"

//TYPEDEF
typedef boost::shared_ptr<Player> SharedPlayer;
typedef boost::shared_ptr<SpaceBox> SharedSpaceBox;

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

    //keys
    bool upKey;
    bool downKey;
    bool leftKey;
    bool rightKey;

    //CONSTRUCTOR
    DISALLOW_COPY_AND_ASSIGN(Level);

//EVENT
private:

    /*!When a key is pressed*/
    void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

    /*!When a key is released*/
    void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
};


#endif