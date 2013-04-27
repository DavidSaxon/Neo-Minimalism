#include "src/states/start_up/StartUp.hpp"

void StartUp::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {

    switch (sym) {

        //TODO: remove this
        case SDLK_F7: {

            //fast kill key
            complete = true;
            break;
        }
    }

}