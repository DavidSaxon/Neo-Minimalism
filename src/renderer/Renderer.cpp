#include "src/renderer/Renderer.hpp"

//CONSTRUCTOR
Renderer::Renderer(SharedEntityList el, SharedDisplay d, SharedCamera cam,
    const util::vec::Vector4D& clearCol, float clipDistance) :
    entityList(el),
    display(d),
	camera(cam),
	clearColour(clearCol),
	clip(clipDistance) {
}

//DESTRUCTOR
Renderer::~Renderer() {
}

//PUBLIC MEMBER FUNCTIONS
void Renderer::init() {

    //initialise sdl
    initSDL();

    display->init();

	//initialise OpenGl
	initGL();
}

void Renderer::render() {

    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    //apply the camera
    camera->apply();

    //get the renderables from the entity list and render them
    RList::iterator
        it = entityList->getRenderables().begin(),
        ite = entityList->getRenderables().end();
    for (; it != ite; ++it) {

        (*it)->render();
    }

    //swap the buffers
    SDL_GL_SwapBuffers();
}

//PRIVATE MEMBER FUNCTIONS
void Renderer::initSDL() {

    //initialise the SDL video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {

        throw omiEx::SDLInitException("SDL video initialisation failure");
    }

    //intialise the timer
    if (SDL_Init(SDL_INIT_TIMER) < 0) {

        throw omiEx::SDLInitException("SDL timer initialisation failure");
    }

    //initialise the audio
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {

        throw omiEx::SDLInitException("SDL audio initialisation failure");
    }
}

void Renderer::initGL() {

    //enable depth testing
    glEnable(GL_DEPTH_TEST);

    //enable blending and transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //cull backwards facing polygons
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //glEnable(GL_LIGHTING);

    //GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; 
    //GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 
    //GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };

    //glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);  
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse); 
    //glLightfv(GL_LIGHT1, GL_POSITION,LightPosition); 

    //glEnable(GL_LIGHT1);

    //glEnable(GL_LIGHT0);

    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // GLfloat lightpos[] = {0.8, 0.0, 0.0, 1.0};
    // glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    //set the clear colour
    glClearColor(clearColour.getX(), clearColour.getY(),
        clearColour.getZ(), clearColour.getF());

    glClearDepth(1000.0);

    //clear for the first time
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //set the projection matrix
    //TODO: get far clipping from user
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float ratio = display->getDim().getX() / display->getDim().getY();

    gluPerspective(45.0f, ratio, 0.0001, clip);

    //set the view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //set pixel mode
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    //enable 2d textures
    glEnable(GL_TEXTURE_2D);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}