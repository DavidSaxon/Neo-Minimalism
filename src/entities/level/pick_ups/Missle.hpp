#ifndef NEOMINIMASILM_ENTITIES_LEVEL_PICKUPS_MISSLE_H_
#	define NEOMINIMASILM_ENTITIES_LEVEL_PICKUPS_MISSLE_H_

#include "src/entity/CollisionType.hpp"
#include "src/physics/bounding/BoundingBox.hpp"

class Missle : public CollisionType {
public:

	Missle(SharedShape s, const util::vec::Vector3D& p);

	~Missle();

	void update();

	void render();

	void collision(col::Type t);

    bool isCollisionType() const {

        return true;
    }

private:

	SharedShape box;
	util::vec::Vector3D rotSpeed;
	util::vec::Vector3D rot;
	util::vec::Vector3D moveSpeed;
};

#endif