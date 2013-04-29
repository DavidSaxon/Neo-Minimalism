#include "src/entities/level/enviroment/Wall.hpp"

Wall::Wall(SharedShape s, const util::vec::Vector3D& p) :
	wall(s) {

	hasNew = false;
	shouldRemove = false;

	pos = p;
}

Wall::~Wall() {
}

void Wall::update() {
}

void Wall::render() {

    glPushMatrix();

    glTranslatef(pos.getX(), pos.getY(), pos.getZ());

    wall->draw();

    glPopMatrix();
}