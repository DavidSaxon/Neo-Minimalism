#include "src/entities/level/enemy/Drone.hpp"

Drone::Drone(SharedShape s,
	const util::vec::Vector3D& p) :
	flyer(s),
	health(4) {

	fireTime = 30;
	fireCounter = static_cast<unsigned>(pos.getZ()) % fireTime;

	pos = p;
	up = false;

    hasNew = false;
    shouldRemove = false;

    util::vec::Vector3D rot;

    bounding = SharedBounding (new BoundingBox(
        util::vec::Vector3D(1.0, 0.8, 1.0), pos, rot));
    type = col::DRONE;
}

Drone::~Drone() {
}

void Drone::update() {

	bounding->setPos(pos);

	if (fireCounter == 0) {

		hasNew = true;
		up = !up;
		fireCounter = fireTime;
	}
	else {

		hasNew = false;
		--fireCounter;
	}

	if (health <= 0) {

		shouldRemove = true;
		hasNew = true;
	}
}

void Drone::render() {

    glPushMatrix();

    glTranslatef(pos.getX(), pos.getY(), pos.getZ());

    flyer->draw();

    glPopMatrix();
}

void Drone::collision(col::Type t) {

	if (t == col::PLAYER_LASOR) {

		health -= 1;
	}
	if (t == col::PLAYER_TORPEDO) {

		health -= 2;
	}
	if (t == col::PLAYER) {

		health = 0;
	}
}

std::vector<SharedEntity> Drone::getNew(SharedResourceManager r) {

	std::vector<SharedEntity> v;

	if (shouldRemove) {

		v.push_back(SharedEntity(new Explosion(
			r->getShape("drone_explosion"), pos, 0.2, 10)));

		unsigned pickup = rand() % 24;

		if (pickup >= 2 && pickup <= 6) {

			v.push_back(SharedEntity(
	        	new Missle(r->getShape("missle"), pos)));

		}

		if (pickup == 1) {

			v.push_back(SharedEntity(
		        new Health(r->getShape("health"), pos)));
		}
	}
	else {

		float x = 0.0;
		float y = ((rand() % 45)) - 22;
		float z = 0.0;

		util::vec::Vector3D rot(x, y, z);

		v.push_back(SharedEntity(
	        new EnemyTorpedo(r->getShape("enemy_torpedo"), rot, pos, up)));
	}
	
	return v;
}