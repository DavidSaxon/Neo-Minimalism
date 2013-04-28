/***************************\
| Lasor fired by the player |
|							|
| @author David Saxon		|
\***************************/

#ifndef NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_PLAYERLASOR_H_
#	define NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_PLAYERLASOR_H_

#include "src/entities/level/effects/Explosion.hpp"
#include "src/entity/CollisionType.hpp"
#include "src/physics/bounding/BoundingBox.hpp"

class PlayerLasor : public CollisionType {
public:

	//CONSTRUCTOR
	PlayerLasor(SharedShape s,
		const util::vec::Vector3D& p);

	~PlayerLasor();

	void update();

	void render();

	void collision(col::Type t);

	std::vector<SharedEntity> getNew(SharedResourceManager r);

    bool isCollisionType() const {

        return true;
    }

private:

	SharedShape lasor;
	float moveSpeed;
	util::vec::Vector3D oPos;
	bool hit;
};

#endif