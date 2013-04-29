#include "src/entities/level/weapons/EnemyTorpedo.hpp"

EnemyTorpedo::EnemyTorpedo(SharedShape s,
	const util::vec::Vector3D& r,
	const util::vec::Vector3D& p,
	bool u) :
	torpedo(s),
	rot(r),
	moveSpeed(-0.3),
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
    type = col::ENEMY_TORPEDO;
}

EnemyTorpedo::~EnemyTorpedo() {
}

void EnemyTorpedo::update() {

	if (hit) {

		shouldRemove = true;
		
		pos.setZ(pos.getZ() + 2 * moveSpeed);
	}
	else {

		move();

		if (pos.getX() <= -14.4 || pos.getX() >= 14.4) {

			hit = true;
		}

		bounding->setPos(pos);
	}
}

void EnemyTorpedo::render() {

	glPushMatrix();

	glTranslatef(pos.getX(), pos.getY(), pos.getZ());

	glRotatef(rot.getX(), -1.0, 0.0, 0.0);
	glRotatef(rot.getY(), 0.0, -1.0, 0.0);
	glRotatef(rot.getZ(), 0.0, 0.0, -1.0);

	torpedo->draw();

	glPopMatrix();
}

void EnemyTorpedo::collision(col::Type t) {

	if (t != col::DRONE && t != col::ENEMY_TORPEDO &&
		t != col::ENEMY_LASOR && t != col::BOSS) {

		hit = true;
	}
}

std::vector<SharedEntity> EnemyTorpedo::getNew(SharedResourceManager r) {

	std::vector<SharedEntity> v;

	v.push_back(SharedEntity(new PlayerTorpedoTrail(
		r->getShape("enemy_torpedo_trail"), rot, pos)));

	//add explosion
	if (shouldRemove) {

		v.push_back(SharedEntity(new Explosion(
			r->getShape("enemy_torpedo_ex"), pos, 0.1, 10)));
	}

	return v;
}

void EnemyTorpedo::move() {

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