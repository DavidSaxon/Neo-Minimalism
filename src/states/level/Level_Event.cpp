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
            turnDir = 1;
            break;
        }
        case SDLK_RIGHT: {

            rightKey = true;
            turnDir = 2;
            break;
        }
        case SDLK_SPACE: {

            spaceKey = true;
            break;
        }
        case SDLK_ESCAPE: {

            pause = !pause;
            break;
        }
        case SDLK_q: {

            if (pause) {

                complete = true;
                exit = true;
            }
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

            if (rightKey) {

                turnDir = 2;
            }
            else {

                turnDir = 0;
            }

            break;
        }
        case SDLK_RIGHT: {

            rightKey = false;

            if (leftKey) {

                turnDir = 1;
            }
            else {

                turnDir = 0;
            }

            break;
        }
        case SDLK_SPACE: {

            spaceKey = false;
            break;
        }
    }
}