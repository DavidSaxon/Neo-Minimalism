#ifndef NEOMINIMALISM_ENTITIES_LEVEL_ENVIROMENT_BELOWPLANET_H_
#	define NEOMINIMALISM_ENTITIES_LEVEL_ENVIROMENT_BELOWPLANET_H_

#include "src/entity/Renderable.hpp"

class BelowPlanet : public Renderable {
public:

	BelowPlanet(SharedShape p, SharedShape s, SharedShape w);

	~BelowPlanet();

	void update();

	void render();

	void renderTransparent();

	void setPos(const util::vec::Vector3D& p) {

		pos = p;
	}

private:

	SharedShape planet;
	SharedShape sun;
	SharedShape wallEnd;
	float move;
};

#endif