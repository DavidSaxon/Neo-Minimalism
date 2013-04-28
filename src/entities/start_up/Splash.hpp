/****************************************\
| Displays and fades in a splash screen. |
|									     |
| @author David Saxon					 |
\****************************************/

#ifndef OMICRON_ENTITIES_SPLASH_H_
#	define OMICRON_ENTITIES_SPLASH_H_

#include "src/entity/Renderable.hpp"

class Splash : public Renderable {
public:

	//CONSTRUCTOR
	/*!Creates a new splash screen
	@s the shape for the splash image
	@f the fader*/
	Splash(SharedShape s, SharedShape f);

	//DESTRUCTOR
	/*!Destroys the splash screen*/
	~Splash();

	//PUBLIC MEMBER FUNCTIONS
	/*!updates the splash screen*/
	void update();

	/*!renders the entity*/
	void render();

	void renderTransparent();

	/*!^INL
	@return true once the fade has completed*/
	bool fadeComplete() const;

private:
	
	//VARIABLES
	//the shape for the splash image
	SharedShape splash;
	//the shape for the fader
	SharedTriangleCol fader;

	//is true once fading is complete
	bool complete;
	//the fade amount of the fader
	float fade;
	//the amount the fader should fade each update
	float fadeAmount;

	//CONSTRUCTOR
	DISALLOW_COPY_AND_ASSIGN(Splash);
};

//INLINE
//PUBLIC MEMBER FUNCTIONS
inline bool Splash::fadeComplete() const {

	return complete;
}

#endif