/*****************************************\
| Represents an entity that is updatable. |
|									      |
| @author David Saxon					  |
\*****************************************/

#ifndef OMICRON_ENTITY_ENTITY_H_
#	define OMICRON_ENTITY_ENTITY_H_

#include <boost/shared_ptr.hpp>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>

#include "src/Utilities/MacroUtil.hpp"
#include "src/Utilities/vector/Vector3D.hpp"

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
};

//INLINE FUNCTIONS
inline ent::EntityType Entity::getType() const {

	return ent::STD;
}

#endif