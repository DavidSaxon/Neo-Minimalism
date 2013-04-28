#ifndef NEOMINIMALISM_ENTITIES_LEVEL_EFFECTS_EXPLOSIONPARTICLE_H_
#	define NEOMINIMALISM_ENTITIES_LEVEL_EFFECTS_EXPLOSIONPARTICLE_H_

#include "src/entity/Renderable.hpp"

class ExplosionParticle : public Renderable {
public:

	ExplosionParticle(SharedShape s,
		const util::vec::Vector3D& r,
		const util::vec::Vector3D& p);

	~ExplosionParticle();

	void update();

	void render();

	void renderTransparent();

private:

	SharedTriangleCol particle;
	util::vec:: Vector3D rot;
	float scale;
	float scaleRate;
	float preScale;
	float lessGreen;

};

#endif