#ifndef NEOMINIMALISM_ENTITIES_ENVIROMENT_WALL_H
#	define NEOMINIMALISM_ENTITIES_ENVIROMENT_WALL_H

#include "src/entity/Renderable.hpp"

class Wall : public Renderable {
public:

	Wall(SharedShape s, const util::vec::Vector3D& p);

	~Wall();

	void update();

	void render();

private:

	SharedShape wall;
};

#endif