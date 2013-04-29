#ifndef NEOMINIMALISM_ENTITES_LEVEL_ENEMY_INTERCEPTOR_H_
#	define NEOMINIMALISM_ENTITES_LEVEL_ENEMY_INTERCEPTOR_H_

#include "src/entities/level/effects/Explosion.hpp"
#include "src/entity/CollisionType.hpp"
#include "src/physics/bounding/BoundingBox.hpp"
#include "src/entities/level/pick_ups/Health.hpp"
#include "src/entities/level/pick_ups/Missle.hpp"
#include "src/entities/level/weapons/EnemyLasor.hpp"

class Interceptor : public CollisionType {
public:

	Interceptor(SharedShape s, SharedShape w, const util::vec::Vector3D& p);

	~Interceptor();

	void update();

	void render();

	void collision(col::Type t);

	std::vector<SharedEntity> getNew(SharedResourceManager r);

    bool isCollisionType() const {

        return true;
    }

private:

	SharedShape flyer;
	SharedShape window;

	int health;
};

#endif