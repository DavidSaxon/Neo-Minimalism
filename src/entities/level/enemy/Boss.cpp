#include "src/entities/level/enemy/Boss.hpp"

Boss::Boss(SharedShape s, SharedShape a) :
	flyer(s),
	arms(a),
	health(400) {

	left = true;

	fire = false;

	torp = true;

	changeTime = 240;
	changeCounter = 0;

	fireTime = 6;
	fireCounter = static_cast<unsigned>(pos.getZ()) % fireTime;

	up = false;

    hasNew = true;
    shouldRemove = false;

    pos.set(0.0, 0.0, -30.0);

    bounding = SharedBounding (new BoundingBox(
        util::vec::Vector3D(8.0, 8.0, 8.0), pos, rot));
    type = col::BOSS;
}

Boss::~Boss() {
}

void Boss::update() {

	rot.setZ(rot.getZ() + 1.0);

	if (left) {

		if (pos.getX() <= 9) {

			pos.setX(pos.getX() + 0.05);
		}
		else {

			left = false;
		}
	}
	else {

		if (pos.getX() >= -9) {

			pos.setX(pos.getX() - 0.05);
		}
		else {

			left = true;
		}
	}

	pos.setZ(pos.getZ() - 0.3);

	bounding->setPos(pos);

	if (fireCounter == 0) {

		fire = true;
		up = !up;
		fireCounter = fireTime;
	}
	else {

		fire = false;
		--fireCounter;
	}

	if (changeCounter == changeTime) {

		if (torp) {

			torp = false;
			fireTime = 40;
		}
		else {

			torp = true;
			fireTime = 6;
		}

		changeCounter = 0;
	}
	else {

		++changeCounter;
	}

	if (health <= 0) {

		shouldRemove = true;
	}
}

void Boss::render() {

    glPushMatrix();

    glTranslatef(pos.getX(), pos.getY(), pos.getZ());

    flyer->draw();

    glRotatef(rot.getX(), 1.0, 0.0, 0.0);
    glRotatef(rot.getY(), 0.0, 1.0, 0.0);
    glRotatef(rot.getZ(), 0.0, 0.0, 1.0);

    glScalef(0.85, 0.85, 0.85);

    arms->draw();

    glPopMatrix();

    glPushMatrix();

    glLoadIdentity();

    //draw the health bar
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor4f(1.0, 0, 0, 1.0);

    glBegin(GL_TRIANGLES);

    float length = 0.03 * (health / 500.0);

    glVertex3f(-length, -0.035, -0.1);
    glVertex3f(-length, -0.038, -0.1);
    glVertex3f( length, -0.035, -0.1);

    glVertex3f( length, -0.038, -0.1);
    glVertex3f( length, -0.035, -0.1);
    glVertex3f(-length, -0.038, -0.1);

    glEnd();

    glPopMatrix();
}

void Boss::collision(col::Type t) {

	if (t == col::PLAYER_LASOR) {

		health -= 1;
	}
	if (t == col::PLAYER_TORPEDO) {

		health -= 2;
	}
	if (t == col::PLAYER) {

		health = 0;
	}
}

std::vector<SharedEntity> Boss::getNew(SharedResourceManager r) {

	std::vector<SharedEntity> v;

	if (shouldRemove) {

		v.push_back(SharedEntity(new Explosion(
			r->getShape("station_explosion"), pos, 6.0, 100, true)));
	}
	else {

		unsigned pickup = rand() % 1000;

		if (pickup == 2 || pickup == 3) {

			v.push_back(SharedEntity(
	        	new Missle(r->getShape("missle"), pos)));

		}

		if (pickup == 1) {

			v.push_back(SharedEntity(
		        new Health(r->getShape("health"), pos)));
		}

		if (fire) {

			if (torp) {

				float x = 0.0;
				float y = ((rand() % 45)) - 22;
				float z = 0.0;

				util::vec::Vector3D rot(x, y, z);

				v.push_back(SharedEntity(
			        new EnemyTorpedo(r->getShape("enemy_torpedo"), rot, pos, up)));
			}
			else {

				for (int i = 0; i < 180; i += 35) {

					float x = 0.0;
					float y = (i - 90) * util::val::degreesToRadians;
					float z = 0.0;

				    float rotMatrix[] = {cos(y)*cos(z), sin(x)*sin(y)*cos(z)-cos(x)*sin(z),
				        sin(x)*sin(z)+cos(x)*sin(y)*cos(z),
				        cos(y)*sin(z), cos(x)*cos(z)+sin(x)*sin(y)*sin(z),
				        cos(x)*sin(y)*sin(z)-sin(x)*cos(z),
				        -sin(y), sin(x)*cos(y), cos(x)*cos(y)};

				    util::vec::Vector3D mS(0.1 * rotMatrix[2],
				        0.1 * rotMatrix[5], (0.5 * rotMatrix[8]));

					v.push_back(SharedEntity(
				        new EnemyLasor(r->getShape("enemy_lasor"), pos, mS)));
				}
			}
		}
	}
	
	return v;
}