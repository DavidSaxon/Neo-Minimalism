#include "src/entities/level/weapons/PlayerLasor.hpp"

PlayerLasor::PlayerLasor(SharedShape s,
	const util::vec::Vector3D& r,
	const util::vec::Vector3D& p,
	const util::vec::Vector3D& ms) :
	lasor(s),
	rot(r),
	moveSpeed(ms) {

	hasNew = false;
	pos = p;
	shouldRemove = false;
}

PlayerLasor::~PlayerLasor() {
}

void PlayerLasor::update() {

	pos += moveSpeed;
}

void PlayerLasor::render() {

	glPushMatrix();

	glTranslatef(pos.getX(), pos.getY(), pos.getZ());

	glRotatef(rot.getX(), -1.0, 0.0, 0.0);
	glRotatef(rot.getY(), 0.0, -1.0, 0.0);
	glRotatef(rot.getZ(), 0.0, 0.0, -1.0);

	lasor->draw();

	glPopMatrix();
}