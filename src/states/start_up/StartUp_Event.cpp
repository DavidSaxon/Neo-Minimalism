#include "src/states/start_up/StartUp.hpp"

void StartUp::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {

    switch (sym) {

        //TODO: remove this
        case SDLK_F7: {

            //fast kill key
            complete = true;
            exit = true;
            break;
        }
        case SDLK_RETURN: {

        	if (atTitle) {

        		entityList->removeEntity(splash);
        		complete = true;
				nextState = SharedSubEngine(new Level());
				nextState->init(resourceManager, entityList, camera);
                Mix_HaltChannel(musicChannel);
        	}
        	break;
        }
    }

}