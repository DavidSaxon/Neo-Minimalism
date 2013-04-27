/*********************************************************************\
| Display is effectly a window that is opened by the Omicron renderer |
|                                                                     |
| @author David Saxon                                                 |
\*********************************************************************/

#ifndef OMICRON_DISPLAY_DISPLAY_H_
#   define OMICRON_DISPLAY_DISPLAY_H_

#include <SDL/SDL.h>

#include <iostream>

#include "src/exceptions/SDLException.hpp"
#include "src/Utilities/MacroUtil.hpp"
#include "src/Utilities/vector/Vector2D.hpp"

class DisplaySurface {
public:

    //CONSTRUCTOR
    /*!Creates a new display
    @dimensions the width and height of the display
    @flags the flags to use for the display*/
    DisplaySurface(util::vec::Vector2D dimensions, bool fullscreen = false);

    //DESTRUCTOR
    /*!Destroys this display*/
    ~DisplaySurface();

    //PUBLIC MEMBER FUNCTIONS
    /*!Creates the new window and displays it*/
    void init();

    /*!Returns the dimensions of the display
    ^INL*/
    const util::vec::Vector2D& getDim() const;

private:

	//VARIABLES
	//the dimensions of the display
	util::vec::Vector2D dim;
    //the window
    SDL_Surface* window;
    //is true if the window should be displayed in full screen mode
    bool full;

    //CONSTRUCTORS
    DISALLOW_COPY_AND_ASSIGN(DisplaySurface);
};

//INLINE
//PUBLIC MEMBER FUNCTIONS
inline const util::vec::Vector2D& DisplaySurface::getDim() const {

    return dim;
}

#endif