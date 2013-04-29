#include "src/entities/level/weapons/EnemyLasor.hpp"

EnemyLasor::EnemyLasor(SharedShape s,
	const util::vec::Vector3D& p,
	const util::vec::Vector3D& ms) :
	lasor(s),
	moveSpeed(ms) {

	hasNew = false;
	pos = p;
	oPos = p;
	shouldRemove = false;

    rotSpeed.set((rand() % 100) / 2.0, (rand() % 100) / 2.0,
        (rand() % 100) / 2.0);

	hit = false;
    bounding = SharedBounding (new BoundingBox(
        util::vec::Vector3D(0.08, 0.08, 0.08), pos, rot));
    type = col::ENEMY_LASOR;
}

EnemyLasor::~EnemyLasor() {
}

void EnemyLasor::update() {

	rot += rotSpeed;

	if (hit) {

		shouldRemove = true;
	}
	else {

		pos += moveSpeed;

		if (fabs(pos.getZ() - oPos.getZ()) > 100) {

			shouldRemove = true;
		}

		bounding->setPos(pos);
	}
}

void EnemyLasor::render() {

	glPushMatrix();

	glTranslatef(pos.getX(), pos.getY(), pos.getZ());

    glRotatef(rot.getX(), 1.0, 0.0, 0.0);
    glRotatef(rot.getY(), 0.0, 1.0, 0.0);
    glRotatef(rot.getZ(), 0.0, 0.0, 1.0);

	lasor->draw();

	glPopMatrix();
}

void EnemyLasor::collision(col::Type t) {

	if (t != col::INTERCEPTOR && t != col::STATION &&
		t!= col::ENEMY_LASOR && t != col::ENEMY_TORPEDO
		&& t != col::BOSS) {

		hit = true;
	}
}