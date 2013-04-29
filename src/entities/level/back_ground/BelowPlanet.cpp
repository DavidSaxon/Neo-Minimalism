#include "src/entities/level/back_ground/BelowPlanet.hpp"

BelowPlanet::BelowPlanet(SharedShape p, SharedShape s, SharedShape w) :
	planet(p),
	sun(s),
	wallEnd(w) {

	move = 0;
    hasNew = false;
    shouldRemove = false;
}

BelowPlanet::~BelowPlanet() {
}

void BelowPlanet::update() {

	move += 0.0005;
}

void BelowPlanet::render() {

	glPushMatrix();

	glTranslatef(pos.getX(), pos.getY(), pos.getZ());

	glTranslatef(-25.0, 10.0, -50.0 + move);

	planet->draw();

	glPopMatrix();

	glPushMatrix();

	glTranslatef(pos.getX(), pos.getY(), pos.getZ());

	//glTranslatef(0, 0, pos.getZ());

	glTranslatef(-9.0, 0.0, -275.0 + move);

	//wallEnd->draw();

	glPopMatrix();
}

void BelowPlanet::renderTransparent() {

	// glPushMatrix();

	// glTranslatef(pos.getX(), pos.getY(), pos.getZ());

	// glTranslatef(18.0, -5.0, -200.0 + move);

	// sun->draw();

	// glPopMatrix();
}