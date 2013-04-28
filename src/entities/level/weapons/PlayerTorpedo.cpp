#include "src/entities/level/weapons/PlayerTorpedo.hpp"

PlayerTorpedo::PlayerTorpedo(SharedShape s,
	const util::vec::Vector3D& r,
	const util::vec::Vector3D& p) :
	torpedo(s),
	rot(r),
	moveSpeed(0.5) {

	shouldRemove = false;
	hasNew = true;
	pos = p;
	oPos = p;
}

PlayerTorpedo::~PlayerTorpedo() {
}

void PlayerTorpedo::update() {

	pos.setZ(pos.getZ() - moveSpeed);

	//if the torpedo has traveled far destroy
	if (fabs(pos.getZ() - oPos.getZ()) > 25) {

		shouldRemove = true;
	}
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

	//add explosion
	if (shouldRemove) {

		v.push_back(SharedEntity(new Explosion(
			r->getShape("explosion_particle"), pos, 1.0)));
	}

	return v;
}