/*****************************************\
| Represents an entity that is updatable. |
|									      |
| @author David Saxon					  |
\*****************************************/

#ifndef OMICRON_ENTITY_ENTITY_H_
#	define OMICRON_ENTITY_ENTITY_H_

#include <boost/shared_ptr.hpp>
#include <cmath>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "src/Utilities/MacroUtil.hpp"
#include "src/Utilities/vector/Vector3D.hpp"

#include "src/resource/ResourceManager.hpp"	

class Entity;

typedef boost::shared_ptr<Entity> SharedEntity;
typedef boost::shared_ptr<ResourceManager> SharedResourceManager;

namespace ent {

	//ENUMERATOR
	//!Thet types of entities*/
	enum EntityType {

		STD = 0,
		RENDERABLE
	};

}

class Entity {
public:

	bool shouldRemove;
	bool hasNew;

	//DESTRUCTOR
	/*!Destroys the entity
	^INL*/
	virtual ~Entity() {
	}

	//PUBLIC MEMBER FUNCTIONS
	/*!Updates the entity*/
	virtual void update() = 0;

	/*!^INL
	@return the type of entity this is*/
	virtual ent::EntityType getType() const;

	virtual std::vector<SharedEntity> getNew(SharedResourceManager r);

	util::vec::Vector3D& getPos();

	virtual bool isCollisionType() const;

protected:

	util::vec::Vector3D pos;
};

//INLINE FUNCTIONS
inline ent::EntityType Entity::getType() const {

	return ent::STD;
}

inline std::vector<SharedEntity> Entity::getNew(SharedResourceManager r) {

	std::vector<SharedEntity> v;

	return v;
}

inline util::vec::Vector3D& Entity::getPos() {

	return pos;
}

inline bool Entity::isCollisionType() const {

	return false;
}

#endif