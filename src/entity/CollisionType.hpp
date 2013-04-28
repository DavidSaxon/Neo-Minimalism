#ifndef OMICRON_ENTITY_COLLISIONTYPE_H_
#	define OMICRON_ENTITY_COLLISIONTYPE_H_

#include <boost/shared_ptr.hpp>

#include "src/entity/Renderable.hpp"
#include "src/physics/bounding/Bounding.hpp"

typedef boost::shared_ptr<Bounding> SharedBounding;

namespace col {

	enum Type {

		ASTEROID = 0,
		PLAYER_LASOR,
		PLAYER_TORPEDO
	};
}

class CollisionType : public Renderable {
public:

	virtual ~CollisionType() {
	}

	virtual void collision(col::Type t) = 0;

	SharedBounding getBounding();

	col::Type getType() {

		return type;
	}

protected:

	SharedBounding bounding;
	col::Type type;
};

inline SharedBounding CollisionType::getBounding() {

	return bounding;
}

#endif