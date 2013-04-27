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
        case SDLK_UP: {

            upKey = true;
            break;
        }
        case SDLK_DOWN: {

            downKey = true;
            break;
        }
        case SDLK_LEFT: {

            leftKey = true;
            break;
        }
        case SDLK_RIGHT: {

            rightKey = true;
            break;
        }
    }

}

void Level::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {

    switch (sym) {

        case SDLK_UP: {

            upKey = false;
            break;
        }
        case SDLK_DOWN: {

            downKey = false;
            break;
        }
        case SDLK_LEFT: {

            leftKey = false;
            break;
        }
        case SDLK_RIGHT: {

            rightKey = false;
            break;
        }
    }
}