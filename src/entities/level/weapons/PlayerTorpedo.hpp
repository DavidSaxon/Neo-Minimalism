#ifndef NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_PLAYERTORPEDO_H_
#	define NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_PLAYERTORPEDO_H_

#include "src/entities/level/effects/Explosion.hpp"
#include "src/entities/level/effects/PlayerTorpedoTrail.hpp"
#include "src/entity/Renderable.hpp"

class PlayerTorpedo : public Renderable {
public:

	PlayerTorpedo(SharedShape s,
		const util::vec::Vector3D& r,
		const util::vec::Vector3D& p);

	~PlayerTorpedo();

	void update();

	void render();

	std::vector<SharedEntity> getNew(SharedResourceManager r);

private:

	SharedShape torpedo;
	float moveSpeed;
	util::vec::Vector3D oPos;
	util::vec::Vector3D rot;
};

#endif