#include "src/states/level/Level.hpp"

void Level::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {

    switch (sym) {

        //TODO: remove this
        case SDLK_F7: {

            //fast kill key
            complete = true;
            exit = true;
            break;
        }
    }

}