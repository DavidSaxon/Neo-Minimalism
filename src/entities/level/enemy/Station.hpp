#ifndef NEOMINIMALISM_ENTITES_LEVEL_ENEMY_STATION_H_
#	define NEOMINIMALISM_ENTITES_LEVEL_ENEMY_STATION_H_

#include "src/entities/level/effects/Explosion.hpp"
#include "src/entity/CollisionType.hpp"
#include "src/physics/bounding/BoundingBox.hpp"
#include "src/entities/level/pick_ups/Health.hpp"
#include "src/entities/level/pick_ups/Missle.hpp"
#include "src/entities/level/weapons/EnemyLasor.hpp"

class Station : public CollisionType {
public:

	Station(SharedShape s, const util::vec::Vector3D& p);

	~Station();

	void update();

	void render();

	void collision(col::Type t);

	std::vector<SharedEntity> getNew(SharedResourceManager r);

    bool isCollisionType() const {

        return true;
    }

private:

	SharedShape flyer;

	int health;

	int fireTime;
	int fireCounter;
};

#endif