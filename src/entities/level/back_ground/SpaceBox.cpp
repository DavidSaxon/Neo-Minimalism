#include "src/entities/level/back_ground/SpaceBox.hpp"

//CONSTRUCTOR
SpaceBox::SpaceBox(SharedShape s) :
    box(s) {
}

//DESTRUCTOR
SpaceBox::~SpaceBox() {
}

//PUBLIC MEMBER FUNCTIONS
void SpaceBox::update() {
}

void SpaceBox::render() {

    glPushMatrix();

    //glTranslatef(-pos.getX(), -pos.getY(), -pos.getZ());

    box->draw();

    glPopMatrix();
}