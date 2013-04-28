#ifndef OMICRON_PHYSICS_BOUNDING_BOUNDINGBOX_H_
#	define OMICRON_PHYSICS_BOUNDING_BOUNDINGBOX_H_

#include "src/physics/bounding/Bounding.hpp"

class BoundingBox : public Bounding {
public:

	BoundingBox(const util::vec::Vector3D& d,
		const util::vec::Vector3D& p,
		const util::vec::Vector3D& r) :
		dim(d) {

		pos = p;
		rot = r;
	}

	~BoundingBox() {
	}

	util::vec::Vector3D& getDim();

	bounding::Type getType() const;

	bool collision(SharedBounding b) const {

		//check for box collision
		if (b->getType() == bounding::BOX) {

			util::vec::Vector3D oPos = b->getPos();
			util::vec::Vector3D oDim =
				boost::dynamic_pointer_cast<BoundingBox>(b)->getDim();

			float aMinX = pos.getX() - (dim.getX() / 2.0);
			float aMaxX = pos.getX() + (dim.getX() / 2.0);
			float aMinY = pos.getY() - (dim.getY() / 2.0);
			float aMaxY = pos.getY() + (dim.getY() / 2.0);
			float aMinZ = pos.getZ() - (dim.getZ() / 2.0);
			float aMaxZ = pos.getZ() + (dim.getZ() / 2.0);

			float bMinX = oPos.getX() - (oDim.getX() / 2.0);
			float bMaxX = oPos.getX() + (oDim.getX() / 2.0);
			float bMinY = oPos.getY() - (oDim.getY() / 2.0);
			float bMaxY = oPos.getY() + (oDim.getY() / 2.0);
			float bMinZ = oPos.getZ() - (oDim.getZ() / 2.0);
			float bMaxZ = oPos.getZ() + (oDim.getZ() / 2.0);

			return (aMaxX >= bMinX && aMinX <= bMaxX
			    && (aMaxY >= bMinY && aMinY <= bMaxY)
			    && (aMaxZ >= bMinZ && aMinZ <= bMaxZ));
		}

		return false;
	}

	void draw();

private:

	util::vec::Vector3D dim;
};

inline util::vec::Vector3D& BoundingBox::getDim() {

	return dim;
}

inline bounding::Type BoundingBox::getType() const {

	return bounding::BOX;
}

inline void BoundingBox::draw() {

    glPushMatrix();

    //std::cout << pos << std::endl;

    glTranslatef(pos.getX(), pos.getY(), pos.getZ());

    glRotatef(rot.getX(), 1.0, 0.0, 0.0);
    glRotatef(rot.getY(), 0.0, 1.0, 0.0);
    glRotatef(rot.getZ(), 0.0, 0.0, 1.0);

	//make sure no textures are bound
	glBindTexture(GL_TEXTURE_2D, 0);

	//set the colour
	glColor4f(0, 1, 0, 1);

    glBegin(GL_LINES);

    float x = dim.getX() / 2.0;
    float y = dim.getY() / 2.0;
    float z = dim.getZ() / 2.0;

    glVertex3f(-x,  y,  z);
    glVertex3f( x,  y,  z);

    glVertex3f( x, -y,  z);
    glVertex3f(-x, -y,  z);

    glVertex3f( x,  y, -z);
    glVertex3f(-x,  y, -z);

    glVertex3f( x, -y, -z);
    glVertex3f(-x, -y, -z);

    glVertex3f( x,  y,  z);
    glVertex3f( x, -y,  z);

    glVertex3f(-x,  y,  z);
    glVertex3f(-x, -y,  z);

    glVertex3f( x,  y, -z);
    glVertex3f( x, -y, -z);

    glVertex3f(-x,  y, -z);
    glVertex3f(-x, -y, -z);

    glVertex3f( x,  y,  z);
    glVertex3f( x,  y, -z);

    glVertex3f(-x,  y,  z);
    glVertex3f(-x,  y, -z);

    glVertex3f( x, -y,  z);
    glVertex3f( x, -y, -z);

    glVertex3f(-x, -y,  z);
    glVertex3f(-x, -y, -z);

    glEnd();

    glPopMatrix();
}

#endif