#include "src/entities/start_up/Splash.hpp"

//CONSTRUCTOR
Splash::Splash(SharedShape s, SharedShape f) :
	splash(s),
	fader(boost::dynamic_pointer_cast<TriangleCol>(f)),
	complete(false),
	fade(1.0),
	fadeAmount(0.01) {
}

//DESTRUCTOR
Splash::~Splash() {
}

//PUBLIC MEMBER FUNCTIONS
void Splash::update() {

	//fade the fader
	if (fade > 0.0) {

		fader->getColour().setF(fade);
		fade -= fadeAmount;
	}
	else {

		complete = true;
	}
}

void Splash::render() {

	splash->draw();
	fader->draw();
}