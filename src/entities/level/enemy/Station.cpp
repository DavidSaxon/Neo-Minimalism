#include "src/entities/level/enemy/Station.hpp"

Station::Station(SharedShape s,
	const util::vec::Vector3D& p) :
	flyer(s),
	health(8) {

	fireTime = 120;
	fireCounter = static_cast<unsigned>(pos.getZ()) % fireTime;

	pos = p;

    hasNew = false;
    shouldRemove = false;

    util::vec::Vector3D rot;

    bounding = SharedBounding (new BoundingBox(
        util::vec::Vector3D(2.0, 0.8, 2.0), pos, rot));
    type = col::STATION;
}

Station::~Station() {
}

void Station::update() {

	bounding->setPos(pos);

	if (fireCounter == 0) {

		hasNew = true;
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

void Station::render() {

    glPushMatrix();

    glTranslatef(pos.getX(), pos.getY(), pos.getZ());

    flyer->draw();

    glPopMatrix();
}

void Station::collision(col::Type t) {

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

std::vector<SharedEntity> Station::getNew(SharedResourceManager r) {

	std::vector<SharedEntity> v;

	if (shouldRemove) {

		v.push_back(SharedEntity(new Explosion(
			r->getShape("station_explosion"), pos, 0.7, 20)));

		unsigned pickup = rand() % 6;

		if (pickup == 2 || pickup == 3 || pickup == 4) {

			v.push_back(SharedEntity(
		        new Health(r->getShape("health"), pos)));
		}

		if (pickup == 1) {

			v.push_back(SharedEntity(
	        	new Missle(r->getShape("missle"), pos)));
		}
	}
	else {

		for (int i = 0; i < 180; i += 18) {

			float x = 0.0;
			float y = (i - 90) * util::val::degreesToRadians;
			float z = 0.0;

		    float rotMatrix[] = {cos(y)*cos(z), sin(x)*sin(y)*cos(z)-cos(x)*sin(z),
		        sin(x)*sin(z)+cos(x)*sin(y)*cos(z),
		        cos(y)*sin(z), cos(x)*cos(z)+sin(x)*sin(y)*sin(z),
		        cos(x)*sin(y)*sin(z)-sin(x)*cos(z),
		        -sin(y), sin(x)*cos(y), cos(x)*cos(y)};

		    util::vec::Vector3D mS(0.1 * rotMatrix[2],
		        0.1 * rotMatrix[5], (0.5 * rotMatrix[8]));

			v.push_back(SharedEntity(
		        new EnemyLasor(r->getShape("enemy_lasor"), pos, mS)));
		}
	}
	
	return v;
}