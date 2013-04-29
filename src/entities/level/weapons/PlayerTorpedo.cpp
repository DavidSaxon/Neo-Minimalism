#include "src/entities/level/weapons/PlayerTorpedo.hpp"

PlayerTorpedo::PlayerTorpedo(SharedShape s,
	const util::vec::Vector3D& r,
	const util::vec::Vector3D& p,
	bool u) :
	torpedo(s),
	rot(r),
	moveSpeed(0.6),
	hit(false),
	goUp(u),
	goDown(!u),
	up(u),
	goStraight(false) {

	shouldRemove = false;
	hasNew = true;
	pos = p;
	oPos = p;

    bounding = SharedBounding (new BoundingBox(
        util::vec::Vector3D(0.08, 0.08, 0.08), pos, rot));
    type = col::PLAYER_TORPEDO;
}

PlayerTorpedo::~PlayerTorpedo() {
}

void PlayerTorpedo::update() {

	if (hit) {

		shouldRemove = true;
		
		pos.setZ(pos.getZ() + 2 * moveSpeed);
	}
	else {

		move();

		bounding->setPos(pos);
	}
}

void PlayerTorpedo::render() {

	glPushMatrix();

	glTranslatef(pos.getX(), pos.getY(), pos.getZ());

	glRotatef(rot.getX(), -1.0, 0.0, 0.0);
	glRotatef(rot.getY(), 0.0, -1.0, 0.0);
	glRotatef(rot.getZ(), 0.0, 0.0, -1.0);

	torpedo->draw();

	glPopMatrix();
}

void PlayerTorpedo::collision(col::Type t) {

	if (t != col::PLAYER && t != col::PLAYER_LASOR &&
		t != col::PLAYER_TORPEDO) {

		hit = true;
	}
}

std::vector<SharedEntity> PlayerTorpedo::getNew(SharedResourceManager r) {

	std::vector<SharedEntity> v;

	v.push_back(SharedEntity(new PlayerTorpedoTrail(
		r->getShape("player_torpedo_trail"), rot, pos)));

	//add explosion
	if (shouldRemove) {

		v.push_back(SharedEntity(new Explosion(
			r->getShape("player_torpedo_explosion_particle"), pos, 0.1, 20)));
	}

	return v;
}

void PlayerTorpedo::move() {

    //short hand rotations
    float x = rot.getX() * util::val::degreesToRadians;
    float y = rot.getY() * util::val::degreesToRadians;
    float z = rot.getZ() * util::val::degreesToRadians;

    float rotMatrix[] = {cos(y)*cos(z), sin(x)*sin(y)*cos(z)-cos(x)*sin(z),
        sin(x)*sin(z)+cos(x)*sin(y)*cos(z),
        cos(y)*sin(z), cos(x)*cos(z)+sin(x)*sin(y)*sin(z),
        cos(x)*sin(y)*sin(z)-sin(x)*cos(z),
        -sin(y), sin(x)*cos(y), cos(x)*cos(y)};

    util::vec::Vector3D moveDis(moveSpeed * rotMatrix[2],
        moveSpeed * rotMatrix[5], -(moveSpeed * rotMatrix[8]));

    pos += moveDis;

	//if the torpedo has traveled far destroy
	if (fabs(pos.getZ() - oPos.getZ()) > 75) {

		shouldRemove = true;
	}

	if (!up) {

		if (goDown) {

			if (rot.getX() >= 12.0) {

				goDown = false;
				goUp = true;		
			}
			else {

				rot.setX(rot.getX() + 1.0);
			}
		}
		if (goUp) {

			if (rot.getX() <= -12.0) {

				goUp = false;
				goStraight = true;
			}
			else {

				rot.setX(rot.getX() - 1.0);
			}
		}
		else if (goStraight) {

			if (rot.getX() >= 0.0) {

				goStraight = false;		
			}
			else {

				rot.setX(rot.getX() + 1.0);
			}
		}
	}
	else {

		if (goDown) {

			if (rot.getX() >= 12.0) {

				goDown = false;
				goStraight = true;		
			}
			else {

				rot.setX(rot.getX() + 1.0);
			}
		}
		if (goUp) {

			if (rot.getX() <= -12.0) {

				goUp = false;
				goDown = true;
			}
			else {

				rot.setX(rot.getX() - 1.0);
			}
		}
		else if (goStraight) {

			if (rot.getX() <= 0.0) {

				goStraight = false;		
			}
			else {

				rot.setX(rot.getX() - 1.0);
			}
		}
	}
}