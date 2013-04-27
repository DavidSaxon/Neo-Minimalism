#include "src/entities/level/weapons/PlayerTorpedo.hpp"

PlayerTorpedo::PlayerTorpedo(SharedShape s,
	const util::vec::Vector3D& r,
	const util::vec::Vector3D& p,
	const util::vec::Vector3D& ms) :
	torpedo(s),
	rot(r),
	moveSpeed(ms) {

	shouldRemove = false;
	hasNew = true;
	pos = p;
}

PlayerTorpedo::~PlayerTorpedo() {
}

void PlayerTorpedo::update() {

	pos += moveSpeed;
}

void PlayerTorpedo::render() {

	glPushMatrix();

	glTranslatef(pos.getX(), pos.getY(), pos.getZ());

	glRotatef(rot.getX(), -1.0, 0.0, 0.0);
	glRotatef(rot.getY(), 0.0, -1.0, 0.0);
	glRotatef(rot.getZ(), 0.0, 0.0, -1.0);

	torpedo->draw();

	glPopMatrix();
}

std::vector<SharedEntity> PlayerTorpedo::getNew(SharedResourceManager r) {

	std::vector<SharedEntity> v;

	v.push_back(SharedEntity(new PlayerTorpedoTrail(
		r->getShape("player_torpedo_trail"), rot, pos)));

	return v;
}