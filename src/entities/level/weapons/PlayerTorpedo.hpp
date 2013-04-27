#ifndef NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_PLAYERTORPEDO_H_
#	define NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_PLAYERTORPEDO_H_

#include "src/entities/level/weapons/PlayerTorpedoTrail.hpp"
#include "src/entity/Renderable.hpp"

class PlayerTorpedo : public Renderable {
public:

	PlayerTorpedo(SharedShape s,
		const util::vec::Vector3D& r,
		const util::vec::Vector3D& p,
		const util::vec::Vector3D& ms);

	~PlayerTorpedo();

	void update();

	void render();

	std::vector<SharedEntity> getNew(SharedResourceManager r);

private:

	SharedShape torpedo;
	util::vec::Vector3D moveSpeed;
	util::vec::Vector3D rot;
};

#endif