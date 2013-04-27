/*****************************************************************\
| The entity list controls the storage and access of all entities |
| 																  |
| @author David Saxon											  |
\*****************************************************************/

#ifndef OMICRON_ENTITYLIST_ENTITYLIST_H_
#	define OMICRON_ENTITYLIST_ENTITYLIST_H_

#include <boost/shared_ptr.hpp>
#include <vector>

#include "src/Utilities/MacroUtil.hpp"

#include "src/entity/Renderable.hpp"

//TYPEDEFS
typedef boost::shared_ptr<Entity> SharedEntity;
typedef boost::shared_ptr<Renderable> SharedRenderable;
typedef std::vector<SharedEntity> EList;
typedef std::vector<SharedRenderable> RList;

class EntityList {
public:

	//CONSTRUCTOR
	/*!Creates a new entity list*/
	EntityList();

	//DESTRUCTOR
	/*!Destroys this entity list*/
	~EntityList();

	//PUBLIC MEMBER FUNCTIONS
	/*!Adds an entity to the entity list
	@entity the entity to add*/
	void addEntity(SharedEntity entity);

	/*!Removes the given entity from the entity list
	@entity the entity to remove*/
	void removeEntity(SharedEntity entity);

	/*!^INL
	@return the entities*/
	EList& getEntities();

	/*!^INL
	@return the renderables*/
	RList& getRenderables();


private:

	//VARIABLES
	//the list of  entities
	EList entityList;
	//the list of renderables
	RList renderableList;

	//CONSTRUCTOR
	DISALLOW_COPY_AND_ASSIGN(EntityList);
};

//INLINE
//PUBLIC MEMBER FUNCTIONS
inline EList& EntityList::getEntities() {

	return entityList;
}

inline RList& EntityList::getRenderables() {

	return renderableList;
}

#endif