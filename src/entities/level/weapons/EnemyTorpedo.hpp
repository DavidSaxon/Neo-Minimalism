#ifndef NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_ENEMYTORPEDO_H_
#	define NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_ENEMYTORPEDO_H_

#include "src/Utilities/ValuesUtil.hpp"

#include "src/entities/level/effects/Explosion.hpp"
#include "src/entities/level/effects/PlayerTorpedoTrail.hpp"
#include "src/entity/CollisionType.hpp"
#include "src/physics/bounding/BoundingBox.hpp"

class EnemyTorpedo : public CollisionType {
public:

	EnemyTorpedo(SharedShape s,
		const util::vec::Vector3D& r,
		const util::vec::Vector3D& p,
		bool u);

	~EnemyTorpedo();

	void update();

	void render();

	void collision(col::Type t);

	std::vector<SharedEntity> getNew(SharedResourceManager r);

    bool isCollisionType() const {

        return true;
    }

	int getDamage() {

		return 5;
	}

private:

	SharedShape torpedo;
	float moveSpeed;
	util::vec::Vector3D oPos;
	util::vec::Vector3D rot;
	bool hit;
	bool goDown;
	bool goUp;
	bool up;
	bool goStraight;

	void move();
};

#endif