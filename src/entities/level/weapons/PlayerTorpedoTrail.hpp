#ifndef NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_PLAYERTORPEDOTRAIL_H_
#	define NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_PLAYERTORPEDOTRAIL_H_

#include "src/entity/Renderable.hpp"

class PlayerTorpedoTrail : public Renderable {
public:

	PlayerTorpedoTrail(SharedShape s,
		const util::vec::Vector3D& r,
		const util::vec::Vector3D& p);

	~PlayerTorpedoTrail();

	void update();

	void render();

	void renderTransparent();

private:

	SharedTriangleCol trail;
	util::vec::Vector3D rot;
	float fade;
	float fadeAmount;
};

#endif