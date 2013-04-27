#include "src/display/DisplaySurface.hpp"

//CONSTRUCTOR
DisplaySurface::DisplaySurface(util::vec::Vector2D dimensions, bool fullscreen) :
	dim(dimensions),
    full(fullscreen),
    window(0) {
}

//DESTRUCTOR
DisplaySurface::~DisplaySurface() {

    delete window;
}

//PUBLIC MEMBER FUNCTIONS
void DisplaySurface::init() {

    //get video info
    const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo(); //get the video info
    //sets the window flags
    int flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE;

    videoInfo->hw_available;

    //check if hardware surfaces can be enabled
    if(videoInfo->hw_available) {

        flags |= SDL_HWSURFACE;
    }
    else {

        flags |= SDL_SWSURFACE;
    }
    //check to see if hardware supports blitting
    if(videoInfo->blit_hw) {

        flags |= SDL_HWACCEL;
    }

    //check if fullscreen mode should be enabled
    if (full) {

        flags |= SDL_FULLSCREEN;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);
     
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,        32);
     
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

    //open in full screen in full resolution
    if (full && (dim.getX() == 0 || dim.getY() == 0)) {

        if ((window = SDL_SetVideoMode(0, 0, 32, flags)) == 0) {

            throw omiEx::SDLWindowException("window failed to open");
        }

        dim.setX(window->w);
        dim.setY(window->h);

        //multi-mointor correction
        while (dim.getX() > 1920) {

            dim.setX(dim.getX() / 2.0);
        }
        while (dim.getY() > 1080) {

            dim.setY(dim.getY() / 2.0);
        }

        //hide the cursor
        SDL_ShowCursor(false);
    }

    //sets up the video mode
    if ((window = SDL_SetVideoMode(dim.getX(), dim.getY(), 32, flags)) == 0) {

        throw omiEx::SDLWindowException("window failed to open");
    }
}