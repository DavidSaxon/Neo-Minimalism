#include "src/entities/level/player/Player.hpp"

//CONSTRUCTOR
Player::Player(SharedShape c, SharedShape h) :
    cockpit(c),
    crossHair(h),
    maxSpeed(0.03),
    currentSpeed(0.03),
    turnSpeed(0.03),
    turnDir(0),
    tiltAngle(5),
    tiltSpeed(1) {

    hasNew = false;
    shouldRemove = false;
}

//DESTRUCTOR
Player::~Player() {
}

//PUBLIC MEMBER FUNCTIONS
/*!updates the player*/
void Player::update() {

    //move the player
    move();

    //tilt the player
    tilt();
}

/*!Renders the player*/
void Player::render() {

    glPushMatrix();

    glLoadIdentity();

    glTranslatef(0.0, 0.0, 0.45);

    cockpit->draw();

    glPopMatrix();
}

void Player::renderTransparent() {

    glPushMatrix();

    glLoadIdentity();

    crossHair->draw();

    glPopMatrix();
}

void Player::noTurn() {

    turnDir = 0;
}

void Player::turnLeft() {

    turnDir = 1;
}

void Player::turnRight() {

    turnDir = 2;
}

//PRIVATE MEMBER FUNCTIONS
void Player::move() {

    util::vec::Vector3D move(0.0, 0.0, -currentSpeed);

    if (turnDir == 1) {

        move.setX(-turnSpeed);
    }
    else if (turnDir == 2) {

        move.setX(turnSpeed);
    }

    pos += move;
}

void Player::tilt() {

    if (turnDir == 0) {

        if (rot.getZ() < 0) {

            rot.setZ(rot.getZ() + tiltSpeed);
        }
        else if (rot.getZ() > 0) {

            rot.setZ(rot.getZ() - tiltSpeed);
        }
    }
    else if (turnDir == 1) {

        if (rot.getZ() > -tiltAngle) {

            rot.setZ(rot.getZ() - tiltSpeed);
        }
    }
    else {

        if (rot.getZ() < tiltAngle) {

            rot.setZ(rot.getZ() + tiltSpeed);
        }
    }
}