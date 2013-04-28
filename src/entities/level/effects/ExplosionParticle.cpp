#include "src/entities/level/effects/ExplosionParticle.hpp"

ExplosionParticle::ExplosionParticle(SharedShape s,
	const util::vec::Vector3D& r,
	const util::vec::Vector3D& p) :
	particle(boost::dynamic_pointer_cast<TriangleCol>(s)),
	rot(r),
	scale(0.0),
	scaleRate(0.1) {

    hasNew = true;
    shouldRemove = false;
    pos = p;

    preScale = (rand() % 100) / 400.0;
    lessGreen = (rand() % 100) / 200.0;
    lessGreen += 0.5;
}

ExplosionParticle::~ExplosionParticle() {
}

void ExplosionParticle::update() {

	//scale
	scale += scaleRate;

	if (scale >= 1.0) {

		shouldRemove = true;
	}
}

void ExplosionParticle::render() {
}

void ExplosionParticle::renderTransparent() {

    glPushMatrix();

    particle->getColour().setY(lessGreen);
	particle->getColour().setF(1.0 - scale);

    glTranslatef(pos.getX(), pos.getY(), pos.getZ());

    glScalef(scale + preScale, scale + preScale, scale + preScale);

	glRotatef(rot.getX(), -1.0, 0.0, 0.0);
	glRotatef(rot.getY(), 0.0, -1.0, 0.0);
	glRotatef(rot.getZ(), 0.0, 0.0, -1.0);

    particle->draw();

    glPopMatrix();
}