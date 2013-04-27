#include "src/entities/level/player/Player.hpp"

//CONSTRUCTOR
Player::Player(SharedShape c, SharedShape h) :
    cockpit(c),
    crossHair(h),
    maxSpeed(0.03),
    currentSpeed(0.03),
    turnSpeed(0.8) {

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

void Player::turnUp() {

    turnRot.setX(turnRot.getX() - turnSpeed);
}

void Player::turnDown() {

    turnRot.setX(turnRot.getX() + turnSpeed);
}

void Player::turnLeft() {

    //tiltRot.setZ(tiltRot.getZ() - leftRightTiltSpeed);
    turnRot.setY(turnRot.getY() - turnSpeed);
}

void Player::turnRight() {

    //tiltRot.setZ(tiltRot.getZ() + leftRightTiltSpeed);
    turnRot.setY(turnRot.getY() + turnSpeed);
}

//PRIVATE MEMBER FUNCTIONS
void Player::move() {

    //short hand rotations
    float x = turnRot.getX() * util::val::degreesToRadians;
    float y = turnRot.getY() * util::val::degreesToRadians;
    float z = turnRot.getZ() * util::val::degreesToRadians;

    float rotMatrix[] = {cos(y)*cos(z), sin(x)*sin(y)*cos(z)-cos(x)*sin(z),
        sin(x)*sin(z)+cos(x)*sin(y)*cos(z),
        cos(y)*sin(z), cos(x)*cos(z)+sin(x)*sin(y)*sin(z),
        cos(x)*sin(y)*sin(z)-sin(x)*cos(z),
        -sin(y), sin(x)*cos(y), cos(x)*cos(y)};

    util::vec::Vector3D move(-(currentSpeed * rotMatrix[2]),
        -(currentSpeed * rotMatrix[5]), currentSpeed * rotMatrix[8]);

    pos += move;
}