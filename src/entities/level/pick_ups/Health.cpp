#include "src/entities/level/pick_ups/Health.hpp"

Health::Health(SharedShape s, const util::vec::Vector3D& p) :
	box(s) {

	pos = p;

    hasNew = false;
    shouldRemove = false;

    //create random rotation speeds
    rotSpeed.set((rand() % 100) / 25.0, (rand() % 100) / 25.0,
        (rand() % 100) / 25.0);

    moveSpeed.set( 0.06 - ((rand() % 100) / 800.0), 0,
        0.06 - ((rand() % 100) / 800.0));

    bounding = SharedBounding (new BoundingBox(
        util::vec::Vector3D(0.5, 0.5, 0.5), pos, rot));
    type = col::HEALTH;
}

Health::~Health() {
}

void Health::update() {

    //increment the rotation
    rot += rotSpeed;

    if (pos.getX() > -14.2 && pos.getX() < 14.2) {

    	pos += moveSpeed;
	}

    bounding->setPos(pos);
}

void Health::render() {

    glPushMatrix();

    glTranslatef(pos.getX(), pos.getY(), pos.getZ());

    glRotatef(rot.getX(), 1.0, 0.0, 0.0);
    glRotatef(rot.getY(), 0.0, 1.0, 0.0);
    glRotatef(rot.getZ(), 0.0, 0.0, 1.0);

    box->draw();

    glPopMatrix();
}

void Health::collision(col::Type t) {

	if (t == col::PLAYER) {

		shouldRemove = true;
	}
}