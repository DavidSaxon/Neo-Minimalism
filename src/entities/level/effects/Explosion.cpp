#include "src/entities/level/effects/Explosion.hpp"

Explosion::Explosion(SharedShape s, util::vec::Vector3D& p,
	float rad) :
	particle(s),
	radius(rad),
	aliveTime(3),
	aliveCounter(0) {

    hasNew = true;
    shouldRemove = false;
    pos = p;
}

Explosion::~Explosion() {
}

void Explosion::update() {

	if (aliveCounter == aliveTime) {

		shouldRemove = true;
	}

	++aliveCounter;
}

std::vector<SharedEntity> Explosion::getNew(
	SharedResourceManager r) {

	std::vector<SharedEntity> v;

	int am = 25 - ((aliveCounter - 1) * 5);

	for (int i = 0; i < am; ++i) {

		//generate random distance from centre
		float dis = (rand() % 100) / 100.0;
		dis *= radius;

		float x = (rand() % 100) / 100.0;
		x *= 360.0;
		float y = (rand() % 100) / 100.0;
		y *= 360.0;
		float z = (rand() % 100) / 100.0;
		z *= 360.0;

		util::vec::Vector3D rot(x, y, z);

        float rotMatrix[] = {cos(y)*cos(z), sin(x)*sin(y)*cos(z)-cos(x)*sin(z),
            sin(x)*sin(z)+cos(x)*sin(y)*cos(z),
            cos(y)*sin(z), cos(x)*cos(z)+sin(x)*sin(y)*sin(z),
            cos(x)*sin(y)*sin(z)-sin(x)*cos(z),
            -sin(y), sin(x)*cos(y), cos(x)*cos(y)};

        util::vec::Vector3D exPos(dis * rotMatrix[2],
            dis * rotMatrix[5], -(dis * rotMatrix[8]));

        exPos += pos;

		v.push_back(SharedEntity(new ExplosionParticle(particle, rot, exPos)));
	}

	return v;
}