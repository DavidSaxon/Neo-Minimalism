/***********************************\
| State representing standard level |
|                                   |
| @author David Saxon               |
\***********************************/

#ifndef OMICRON_STATES_LEVEL_H_
#   define OMICRON_STATES_LEVEL_H_

#include "src/sub_engine/SubEngine.hpp"

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

//EVENT
private:

    /*!When a key is pressed*/
    void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
};


#endif