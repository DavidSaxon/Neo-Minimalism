#ifndef NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_PLAYERTORPEDO_H_
#	define NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_PLAYERTORPEDO_H_

#include "src/entities/level/effects/Explosion.hpp"
#include "src/entities/level/effects/PlayerTorpedoTrail.hpp"
#include "src/entity/CollisionType.hpp"
#include "src/physics/bounding/BoundingBox.hpp"

class PlayerTorpedo : public CollisionType {
public:

	PlayerTorpedo(SharedShape s,
		const util::vec::Vector3D& r,
		const util::vec::Vector3D& p);

	~PlayerTorpedo();

	void update();

	void render();

	void collision(col::Type t);

	std::vector<SharedEntity> getNew(SharedResourceManager r);

    bool isCollisionType() const {

        return true;
    }

private:

	SharedShape torpedo;
	float moveSpeed;
	util::vec::Vector3D oPos;
	util::vec::Vector3D rot;
	bool hit;
};

#endif