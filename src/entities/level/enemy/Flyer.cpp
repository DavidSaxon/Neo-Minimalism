#include "src/entities/level/enemy/Flyer.hpp"

Flyer::Flyer(SharedShape s, SharedShape w,
	const util::vec::Vector3D& p) :
	flyer(s),
	window(w),
	health(1) {

	pos = p;

    hasNew = false;
    shouldRemove = false;

    util::vec::Vector3D rot;

    bounding = SharedBounding (new BoundingBox(
        util::vec::Vector3D(0.8, 0.8, 0.8), pos, rot));
    type = col::FLYER;
}

Flyer::~Flyer() {
}

void Flyer::update() {

	bounding->setPos(pos);

	if (health <= 0) {

		shouldRemove = true;
		hasNew = true;
	}
}

void Flyer::render() {

    glPushMatrix();

    glTranslatef(pos.getX(), pos.getY(), pos.getZ());

    flyer->draw();

    window->draw();

    glPopMatrix();
}

void Flyer::collision(col::Type t) {

	if (t == col::PLAYER_LASOR) {

		health -= 1;
	}
	if (t == col::PLAYER_TORPEDO || t == col::PLAYER) {

		health = 0;
	}
}

std::vector<SharedEntity> Flyer::getNew(SharedResourceManager r) {

	std::vector<SharedEntity> v;

	v.push_back(SharedEntity(new Explosion(
		r->getShape("flyer_explosion"), pos, 0.1, 50)));

	unsigned pickup = rand() % 50;

	if (pickup == 4) {

		v.push_back(SharedEntity(
	        new Health(r->getShape("health"), pos)));
	}

	if (pickup == 35 || pickup == 1 || pickup == 2) {

		v.push_back(SharedEntity(
        	new Missle(r->getShape("missle"), pos)));
	}
	
	return v;
}