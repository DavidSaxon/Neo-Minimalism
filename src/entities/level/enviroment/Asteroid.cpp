#include "src/entities/level/enviroment/Asteroid.hpp"

//CONSTRUCTOR
Asteroid::Asteroid(SharedShape s, const util::vec::Vector3D& p) :
    asteroid(s) {

    pos = p;

    hasNew = false;
    shouldRemove = false;

    //create random rotation speeds
    rotSpeed.set((rand() % 100) / 400.0, (rand() % 100) / 400.0,
        (rand() % 100) / 400.0);
}

//DESTRUCTOR
Asteroid::~Asteroid() {
}

//PUBLIC MEMBER FUNCTIONS
/*!updates the asteroid*/
void Asteroid::update() {

    //increment the rotation
    rot += rotSpeed;
}

/*!renders the asteroid*/
void Asteroid::render() {

    //apply translations to the asteroid
    glPushMatrix();

    glTranslatef(pos.getX(), pos.getY(), pos.getZ());

    glRotatef(rot.getX(), 1.0, 0.0, 0.0);
    glRotatef(rot.getY(), 0.0, 1.0, 0.0);
    glRotatef(rot.getZ(), 0.0, 0.0, 1.0);

    asteroid->draw();

    glPopMatrix();
}