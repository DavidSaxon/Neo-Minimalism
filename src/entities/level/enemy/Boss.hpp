#ifndef NEOMINIMALISM_ENTITES_LEVEL_ENEMY_BOSS_H_
#	define NEOMINIMALISM_ENTITES_LEVEL_ENEMY_BOSS_H_

#include "src/entities/level/effects/Explosion.hpp"
#include "src/entity/CollisionType.hpp"
#include "src/physics/bounding/BoundingBox.hpp"
#include "src/entities/level/pick_ups/Health.hpp"
#include "src/entities/level/pick_ups/Missle.hpp"
#include "src/entities/level/weapons/EnemyLasor.hpp"
#include "src/entities/level/weapons/EnemyTorpedo.hpp"

class Boss : public CollisionType {
public:

	int health;

	Boss(SharedShape s, SharedShape a);

	~Boss();

	void update();

	void render();

	void collision(col::Type t);

	std::vector<SharedEntity> getNew(SharedResourceManager r);

    bool isCollisionType() const {

        return true;
    }

private:

	SharedShape flyer;
	SharedShape arms;

	util::vec::Vector3D rot;

	int fireTime;
	int fireCounter;

	int changeTime;
	int changeCounter;

	bool torp;

	bool fire;

	bool left;

	bool up;
};

#endif