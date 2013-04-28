#include "src/entities/level/weapons/PlayerTorpedo.hpp"

PlayerTorpedo::PlayerTorpedo(SharedShape s,
	const util::vec::Vector3D& r,
	const util::vec::Vector3D& p) :
	torpedo(s),
	rot(r),
	moveSpeed(0.5),
	hit(false) {

	shouldRemove = false;
	hasNew = true;
	pos = p;
	oPos = p;

    bounding = SharedBounding (new BoundingBox(
        util::vec::Vector3D(0.08, 0.08, 0.08), pos, rot));
    type = col::PLAYER_TORPEDO;
}

PlayerTorpedo::~PlayerTorpedo() {
}

void PlayerTorpedo::update() {

	if (hit) {

		shouldRemove = true;
		
		pos.setZ(pos.getZ() + 2 * moveSpeed);
	}
	else {

		pos.setZ(pos.getZ() - moveSpeed);

		//if the torpedo has traveled far destroy
		if (fabs(pos.getZ() - oPos.getZ()) > 100) {

			shouldRemove = true;
		}

		bounding->setPos(pos);
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

void PlayerTorpedo::collision(col::Type t) {

	if (t == col::ASTEROID) {

		hit = true;
	}
}

std::vector<SharedEntity> PlayerTorpedo::getNew(SharedResourceManager r) {

	std::vector<SharedEntity> v;

	v.push_back(SharedEntity(new PlayerTorpedoTrail(
		r->getShape("player_torpedo_trail"), rot, pos)));

	//add explosion
	if (shouldRemove) {

		v.push_back(SharedEntity(new Explosion(
			r->getShape("player_torpedo_explosion_particle"), pos, 0.1, 50)));
	}

	return v;
}