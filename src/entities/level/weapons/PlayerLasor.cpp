#include "src/entities/level/weapons/PlayerLasor.hpp"

PlayerLasor::PlayerLasor(SharedShape s,
	const util::vec::Vector3D& p) :
	lasor(s),
	moveSpeed(0.5) {

	hasNew = false;
	pos = p;
	oPos = p;
	shouldRemove = false;

	hit = false;
	util::vec::Vector3D rot;
    bounding = SharedBounding (new BoundingBox(
        util::vec::Vector3D(0.08, 0.08, 0.08), pos, rot));
    type = col::PLAYER_LASOR;
}

PlayerLasor::~PlayerLasor() {
}

void PlayerLasor::update() {

	if (hit) {

		shouldRemove = true;
		hasNew = true;

		pos.setZ(pos.getZ() + 2 * moveSpeed);
	}
	else {

		pos.setZ(pos.getZ() - moveSpeed);

		if (fabs(pos.getZ() - oPos.getZ()) > 100) {

			shouldRemove = true;
		}

		bounding->setPos(pos);
	}
}

void PlayerLasor::render() {

	glPushMatrix();

	glTranslatef(pos.getX(), pos.getY(), pos.getZ());

	lasor->draw();

	glPopMatrix();
}

void PlayerLasor::collision(col::Type t) {

	if (t == col::ASTEROID) {

		hit = true;
	}
}

std::vector<SharedEntity> PlayerLasor::getNew(SharedResourceManager r) {

	std::vector<SharedEntity> v;

	v.push_back(SharedEntity(new Explosion(
		r->getShape("player_lasor_explosion_particle"), pos, 0.05, 25)));

	return v;
}