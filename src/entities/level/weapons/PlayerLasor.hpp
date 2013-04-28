/***************************\
| Lasor fired by the player |
|							|
| @author David Saxon		|
\***************************/

#ifndef NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_PLAYERLASOR_H_
#	define NEOMINIMALISM_ENTITIES_LEVEL_WEAPONS_PLAYERLASOR_H_

#include "src/entity/Renderable.hpp"

class PlayerLasor : public Renderable {
public:

	//CONSTRUCTOR
	PlayerLasor(SharedShape s,
		const util::vec::Vector3D& p);

	~PlayerLasor();

	void update();

	void render();

private:

	SharedShape lasor;
	float moveSpeed;
	util::vec::Vector3D oPos;
};

#endif