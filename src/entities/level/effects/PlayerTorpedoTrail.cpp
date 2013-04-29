#include "src/entities/level/effects/PlayerTorpedoTrail.hpp"

PlayerTorpedoTrail::PlayerTorpedoTrail(SharedShape s,
	const util::vec::Vector3D& r,
	const util::vec::Vector3D& p) :
	trail(boost::dynamic_pointer_cast<TriangleCol>(s)),
	rot(r),
	fade(0.6),
	fadeAmount(0.03) {

	shouldRemove = false;
	pos = p;
}

PlayerTorpedoTrail::~PlayerTorpedoTrail() {
}

void PlayerTorpedoTrail::update() {

	//fade the fader
	if (fade > 0.0) {

		fade -= fadeAmount;
	}
	else {

		shouldRemove = true;
	}
}

void PlayerTorpedoTrail::render() {
}

void PlayerTorpedoTrail::renderTransparent() {

	glPushMatrix();

	trail->getColour().setF(fade);

	glTranslatef(pos.getX(), pos.getY(), pos.getZ());

	glRotatef(rot.getX(), -1.0, 0.0, 0.0);
	glRotatef(rot.getY(), 0.0, -1.0, 0.0);
	glRotatef(rot.getZ(), 0.0, 0.0, -1.0);

	trail->draw();

	glPopMatrix();
}