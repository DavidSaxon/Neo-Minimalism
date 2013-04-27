/******************************************************\
| Represents a shape that is drawable by the renderer. |
|													   |
| @author David Saxon								   |
\******************************************************/

#ifndef OMICRON_SHAPE_SHAPE_H_
#	define OMICRON_SHAPE_SHAPE_H_

#include <boost/shared_ptr.hpp>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>

#include "src/Utilities/vector/Vector2D.hpp"
#include "src/Utilities/vector/Vector3D.hpp"
#include "src/Utilities/vector/Vector4D.hpp"

//TYPEDEFS
typedef boost::shared_ptr<util::vec::Vector2D> SharedVec2D;
typedef boost::shared_ptr<util::vec::Vector3D> SharedVec3D;
typedef std::vector<SharedVec2D> TexCoords;
typedef std::vector<SharedVec3D> VertexCoords;

class Shape {
public:

	//DESTRUCTOR
	/*!destroys the shape
	^INL*/
	~Shape() {
	}

	//PUBLIC MEMBER FUNCTIONS
	/*!draws the shape*/
	virtual void draw() = 0;
};

#endif