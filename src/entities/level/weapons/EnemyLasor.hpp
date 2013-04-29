#ifndef NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_ENEMYLASOR_H_
#	define NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_ENEMYLASOR_H_

#include "src/entities/level/effects/Explosion.hpp"
#include "src/entity/CollisionType.hpp"
#include "src/physics/bounding/BoundingBox.hpp"

class EnemyLasor : public CollisionType {
public:

	//CONSTRUCTOR
	EnemyLasor(SharedShape s,
		const util::vec::Vector3D& p,
		const util::vec::Vector3D& ms);

	~EnemyLasor();

	void update();

	void render();

	void collision(col::Type t);

    bool isCollisionType() const {

        return true;
    }

	int getDamage() {

		return 1;
	}

private:

	SharedShape lasor;
	util::vec::Vector3D moveSpeed;
	util::vec::Vector3D rot;
	util::vec::Vector3D rotSpeed;
	util::vec::Vector3D oPos;
	bool hit;
};

#endif