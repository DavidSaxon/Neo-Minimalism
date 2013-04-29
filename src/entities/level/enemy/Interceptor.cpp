#include "src/entities/level/enemy/Interceptor.hpp"

Interceptor::Interceptor(SharedShape s, SharedShape w,
	const util::vec::Vector3D& p) :
	flyer(s),
	window(w),
	health(2) {

	pos = p;

    hasNew = false;
    shouldRemove = false;

    util::vec::Vector3D rot;

    bounding = SharedBounding (new BoundingBox(
        util::vec::Vector3D(0.8, 0.8, 0.8), pos, rot));
    type = col::INTERCEPTOR;
}

Interceptor::~Interceptor() {
}

void Interceptor::update() {

	bounding->setPos(pos);

	unsigned fire = rand() % 60;

	if (fire == 2) {

		hasNew = true;
	}
	else {

		hasNew = false;
	}

	if (health <= 0) {

		shouldRemove = true;
		hasNew = true;
	}
}

void Interceptor::render() {

    glPushMatrix();

    glTranslatef(pos.getX(), pos.getY(), pos.getZ());

    flyer->draw();

    window->draw();

    glPopMatrix();
}

void Interceptor::collision(col::Type t) {

	if (t == col::PLAYER_LASOR) {

		health -= 1;
	}
	if (t == col::PLAYER_TORPEDO || t == col::PLAYER) {

		health = 0;
	}
}

std::vector<SharedEntity> Interceptor::getNew(SharedResourceManager r) {

	std::vector<SharedEntity> v;

	if (shouldRemove) {

		v.push_back(SharedEntity(new Explosion(
			r->getShape("interceptor_explosion"), pos, 0.15, 50)));

		unsigned pickup = rand() % 35;

		if (pickup == 1) {

			v.push_back(SharedEntity(
		        new Health(r->getShape("health"), pos)));
		}

		if (pickup > 1 && pickup < 8) {

			v.push_back(SharedEntity(
	        	new Missle(r->getShape("missle"), pos)));
		}
	}
	else {

		float x = 0.0;
		float y = ((rand() % 180) - 90) * util::val::degreesToRadians;
		float z = 0.0;

	    float rotMatrix[] = {cos(y)*cos(z), sin(x)*sin(y)*cos(z)-cos(x)*sin(z),
	        sin(x)*sin(z)+cos(x)*sin(y)*cos(z),
	        cos(y)*sin(z), cos(x)*cos(z)+sin(x)*sin(y)*sin(z),
	        cos(x)*sin(y)*sin(z)-sin(x)*cos(z),
	        -sin(y), sin(x)*cos(y), cos(x)*cos(y)};

	    util::vec::Vector3D mS(0.1 * rotMatrix[2],
	        0.1 * rotMatrix[5], (1.0 * rotMatrix[8]));

		v.push_back(SharedEntity(
	        new EnemyLasor(r->getShape("enemy_lasor"), pos, mS)));
	}
	
	return v;
}