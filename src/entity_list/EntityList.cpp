#include "src/entity_list/EntityList.hpp"

//CONSTRUCTOR
EntityList::EntityList() {
}

//DESTRUCTOR
EntityList::~EntityList() {
}

//PUBLIC MEMBER FUNCTIONS
void EntityList::addEntity(SharedEntity entity) {

	//add to the entity list
	entityList.push_back(entity);

    if (entity->isCollisionType()) {

        collisionList.push_back(
           boost::dynamic_pointer_cast<CollisionType>(entity));

    }

	//check if renderable
	if (entity->getType() == ent::RENDERABLE) {

		//add to the renderable list
		renderableList.push_back(
			boost::dynamic_pointer_cast<Renderable>(entity));
	}
}

void EntityList::removeEntity(SharedEntity entity) {

    //remove from the list of all entities
    EList::iterator it = entityList.begin();
    for (; it != entityList.end();) {

        if (*it == entity) {

            it = entityList.erase(it);
        }
        else {

            ++it;
        }
    }

    if (entity->isCollisionType()) {

        CList::iterator cit = collisionList.begin();
        for (; cit != collisionList.end();) {

            if (*cit == boost::dynamic_pointer_cast<CollisionType>(entity)) {

                cit = collisionList.erase(cit);
            }
            else {

                ++cit;
            }
        }
    }

    //if renderable remove from the renderable list
    if (entity->getType() == ent::RENDERABLE) {

        RList::iterator rit = renderableList.begin();
        for (; rit != renderableList.end();) {

            if (*rit == entity) {

                rit = renderableList.erase(rit);
            }
            else {

                ++rit;
            }
        }
    }
}