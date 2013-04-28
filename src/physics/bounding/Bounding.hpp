#ifndef OMICRON_PHYSICS_BOUNDING_BOUNDING_H_
#	define OMICRON_PHYSICS_BOUNDING_BOUNDING_H_

#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "src/Utilities/vector/Vector3D.hpp"

class Bounding;

typedef boost::shared_ptr<Bounding> SharedBounding;

namespace bounding {

enum Type {

	BOX = 0,
	SPHERE
};

}

class Bounding {
public:

	virtual ~Bounding() {
	}

	util::vec::Vector3D& getPos();

	util::vec::Vector3D& getRot();

	void setPos(const util::vec::Vector3D& p);

	void setRot(const util::vec::Vector3D& r);

	virtual bounding::Type getType() const = 0;

	virtual bool collision(SharedBounding b) const = 0;

	virtual void draw();

protected:

	util::vec::Vector3D pos;
	util::vec::Vector3D rot;

};

inline util::vec::Vector3D& Bounding::getPos() {

	return pos;
}

inline util::vec::Vector3D& Bounding::getRot() {

	return rot;
}

inline void Bounding::setPos(const util::vec::Vector3D& p) {

	pos = p;
}

inline void Bounding::setRot(const util::vec::Vector3D& r) {

	rot = r;
}

inline void Bounding::draw() {

	//do nothing
}

#endif