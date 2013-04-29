#ifndef NEOMINIMALISM_ENTITES_LEVEL_ENEMY_FLYER_H_
#	define NEOMINIMALISM_ENTITES_LEVEL_ENEMY_FLYER_H_

#include "src/entities/level/effects/Explosion.hpp"
#include "src/entity/CollisionType.hpp"
#include "src/physics/bounding/BoundingBox.hpp"
#include "src/entities/level/pick_ups/Health.hpp"
#include "src/entities/level/pick_ups/Missle.hpp"

class Flyer : public CollisionType {
public:

	Flyer(SharedShape s, SharedShape w, const util::vec::Vector3D& p);

	~Flyer();

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