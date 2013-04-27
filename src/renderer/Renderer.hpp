/*************************\
| The renderer of omicron |
|					      |
| @author David Saxon     |
\*************************/

#ifndef OMICRON_RENDERER_RENDERER_H_
#	define OMICRON_RENDERER_RENDERER_H_

#include <boost/shared_ptr.hpp>
#include <iostream>

#include "src/Utilities/MacroUtil.hpp"
#include "src/Utilities/vector/Vector4D.hpp"

#include "src/camera/Camera.hpp"
#include "src/display/DisplaySurface.hpp"
#include "src/entity_list/EntityList.hpp"
#include "src/exceptions/SDLException.hpp"

//TYPEDEFS
typedef boost::shared_ptr<DisplaySurface> SharedDisplay;
typedef boost::shared_ptr<EntityList> SharedEntityList;
typedef boost::shared_ptr<Camera> SharedCamera;

class Renderer {
public:

	//CONSTRUCTOR
	/*!Creates a new renderer
	@el the entity list
	@d the display to render to
	@clearCol the clear colour for the renderer to use
	@clipDistance the clip distance of the renderer*/
	Renderer(SharedEntityList el, SharedDisplay d, SharedCamera cam,
		const util::vec::Vector4D& clearCol, float clipDistance);

	//DESTRUCTOR
	/*!Destroys this renderer*/
	~Renderer();

	//PUBLIC MEMBER FUNCTIONS
	/*!Initialises the renderer*/
	void init();

	/*!Renders to the display*/
	void render();

private:

	//VARIABLES
	//the display to render to
	SharedDisplay display;
	//the entity list
	SharedEntityList entityList;
	//the camera to use
	SharedCamera camera;

	//the clear colour
	util::vec::Vector4D clearColour;
	//the clipping distance
	float clip;

	//CONSTRUCTOR
	DISALLOW_COPY_AND_ASSIGN(Renderer);

	//PRIVATE MEMBER FUNCTIONS
	/*!Initialise SDL*/
	void initSDL();

	/*Initialise the OpenGL*/
	void initGL();
};

#endif