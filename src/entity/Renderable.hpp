/*******************************************************\
| Represents an entity that is drawable by the renderer |
|														|
| @author David Saxon									|
\*******************************************************/

#ifndef OMICRON_ENTITY_RENDERABLE_H_
#	define OMICRON_ENTITY_RENDERABLE_H_

#include "src/entity/Entity.hpp"
#include "src/shape/Shape.hpp"
#include "src/shape/triangle/TriangleCol.hpp"
#include "src/shape/triangle/TriangleTex.hpp"

//TYPEDEFS
typedef boost::shared_ptr<Shape> SharedShape;
typedef boost::shared_ptr<TriangleCol> SharedTriangleCol;
typedef boost::shared_ptr<TriangleTex> SharedTriangleTex;

class Renderable : public Entity {
public:

	//DESTRUCTOR
	/*!Destroys the renderable
	^INL*/
	virtual ~Renderable() {
	}

	//PUBLIC MEMBER FUNCTIONS
	/*!Renders the renderable*/
	virtual void render() = 0;

	/*!^INL
	@return the type of entity this is*/
	ent::EntityType getType() const;
};

//INLINE FUCTIONS
inline ent::EntityType Renderable::getType() const {

	return ent::RENDERABLE;
}

#endif