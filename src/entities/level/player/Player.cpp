#include "src/entities/level/player/Player.hpp"

//CONSTRUCTOR
Player::Player(SharedShape c, SharedShape h, SharedShape f) :
    cockpit(c),
    crossHair(h),
    fader(boost::dynamic_pointer_cast<TriangleCol>(f)),
    maxSpeed(0.3),
    currentSpeed(0.3),
    turnSpeed(0.3),
    turnDir(0),
    tiltAngle(5),
    tiltSpeed(0.5),
    health(100),
    maxHealth(100),
    dead(false),
    fade(1.0) {

    hasNew = false;
    shouldRemove = false;
    torpedo = false;
    torpedoTime = 500;
    torpedoCounter = 0;

    bounding = SharedBounding (new BoundingBox(
        util::vec::Vector3D(0.5, 0.5, 3.0), pos, rot));
    type = col::PLAYER;
}

//DESTRUCTOR
Player::~Player() {
}

//PUBLIC MEMBER FUNCTIONS
/*!updates the player*/
void Player::update() {

    //move the player
    if (!dead) {

        move();
    }

    //tilt the player
    tilt();

    if (torpedoCounter == 0) {

        torpedo = false;
    }
    else {

        --torpedoCounter;
    }

    if (health <= 0) {

        dead = true;
    }

    if (fade > 0) {

        fader->getColour().setF(fade);

        fade -= 0.02;
    }
}

/*!Renders the player*/
void Player::render() {

    if (!dead) {

        glPushMatrix();

        glLoadIdentity();

        //draw the health bar
        glBindTexture(GL_TEXTURE_2D, 0);
        glColor4f(1.0 - (health / 100.0), (health / 100.0), 0, 1.0);

        glBegin(GL_TRIANGLES);

        float length = 0.03 * (health / 100.0);

        glVertex3f(-length, 0.038, -0.1);
        glVertex3f(-length, 0.035, -0.1);
        glVertex3f( length, 0.038, -0.1);

        glVertex3f( length, 0.035, -0.1);
        glVertex3f( length, 0.038, -0.1);
        glVertex3f(-length, 0.035, -0.1);

        glEnd();

        glTranslatef(0.0, 0.0, 0.45);

        cockpit->draw();

        glPopMatrix();
    }
}

void Player::renderTransparent() {

    if (!dead) {

        glPushMatrix();

        glLoadIdentity();

        crossHair->draw();

        if (fade > 0) {

            fader->draw();
        }

        glPopMatrix();
    }
}

void Player::collision(col::Type t) {

    if (t == col::ASTEROID) {

        health = 0;
    }
    if (t == col::FLYER || t == col::INTERCEPTOR || t == col::DRONE) {

        health -= 10;
    }
    if (t == col::HEALTH) {

        health += 100;

        if (health > maxHealth) {

            health = maxHealth;
        }
    }
    if (t == col::MISSLE) {

        torpedo = true;
        torpedoCounter = torpedoTime;
    }
    if (t == col::ENEMY_LASOR) {

        health -= 3;
    }
    if (t == col::ENEMY_TORPEDO) {

        health -= 6;
    }
    if (t == col::STATION) {

        health -= 25;
    }
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

        if (pos.getX() >= -14.2) {

            move.setX(-turnSpeed);
        }
    }
    else if (turnDir == 2) {

        if (pos.getX() <= 14.2) {

            move.setX(turnSpeed);
        }
    }

    pos += move;

    bounding->setPos(pos);
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