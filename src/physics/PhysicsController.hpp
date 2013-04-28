#ifndef OMICRON_PHYSICS_PHYSICSCONTROLLER_H_
#	define OMICRON_PHYSICS_PHYSICSCONTROLLER_H_

#include <boost/shared_ptr.hpp>
#include <iostream>

#include "src/entity_list/EntityList.hpp"
#include "src/physics/bounding/BoundingBox.hpp"

typedef boost::shared_ptr<EntityList> SharedEntityList;

class PhysicsController {
public:

	PhysicsController(SharedEntityList el);

	~PhysicsController();

	void update();

private:

	SharedEntityList entities;
};

#endif