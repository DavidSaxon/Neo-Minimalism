#include "src/entities/level/weapons/PlayerLasor.hpp"

PlayerLasor::PlayerLasor(SharedShape s,
	const util::vec::Vector3D& p) :
	lasor(s),
	moveSpeed(0.5) {

	hasNew = false;
	pos = p;
	oPos = p;
	shouldRemove = false;
}

PlayerLasor::~PlayerLasor() {
}

void PlayerLasor::update() {

	pos.setZ(pos.getZ() - moveSpeed);

	if (fabs(pos.getZ() - oPos.getZ()) > 100) {

		shouldRemove = true;
	}
}

void PlayerLasor::render() {

	glPushMatrix();

	glTranslatef(pos.getX(), pos.getY(), pos.getZ());

	lasor->draw();

	glPopMatrix();
}