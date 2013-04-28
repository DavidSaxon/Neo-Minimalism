#ifndef NEOMINIMALISM_ENTITIES_LEVEL_EFFECTS_EXPLOSION_H_
#	define NEOMINIMALISM_ENTITIES_LEVEL_EFFECTS_EXPLOSION_H_

#include "src/entities/level/effects/ExplosionParticle.hpp"
#include "src/entity/Entity.hpp"

class Explosion : public Entity {
public:

	Explosion(SharedShape s, util::vec::Vector3D& p,
		float rad);

	~Explosion();

	void update();

	std::vector<SharedEntity> getNew(SharedResourceManager r);

private:

	SharedShape particle;
	float radius;
	unsigned aliveTime;
	unsigned aliveCounter;
};

#endif