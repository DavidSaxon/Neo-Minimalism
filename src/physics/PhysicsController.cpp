#include "src/physics/PhysicsController.hpp"

PhysicsController::PhysicsController(SharedEntityList el) :
	entities(el) {
}

PhysicsController::~PhysicsController() {
}

void PhysicsController::update() {

	//get the physics entities and check for collisions
	CList en = entities->getCollisions();

	for (unsigned i = 0; i < en.size(); ++i) {
		for (unsigned j = 0; j < en.size(); ++j) {


			if (j == i) {

				continue;
			}

			if (en[i]->getBounding()->collision(en[j]->getBounding())) {

				en[i]->collision(en[j]->getType());
			}
		}
	}
}