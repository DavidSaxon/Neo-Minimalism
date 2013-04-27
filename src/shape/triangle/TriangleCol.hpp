/*********************************\
| Represents a coloured triagnle. |
|								  |
| @author David Saxon		      |
\*********************************/

#ifndef OMICRON_SHAPE_TRIANGLE_TRIANGLECOL_H_
#	define OMICRON_SHAPE_TRIANGLE_TRIANGLECOL_H_

#include <iostream>

#include "src/shape/Shape.hpp"

class TriangleCol : public Shape {
public:

	//CONSTRUCTOR
	/*!Creates a new coloured triangle
	@col the colour of the triangle
	@vCoords the vertex co-ordinates of the triangle*/
	TriangleCol(const util::vec::Vector4D& col, VertexCoords& vCoords);

	//DESTRUCTOR
	/*!Destroys the triangle*/
	~TriangleCol();

	//PUBLIC MEMBER FUNCTIONS
	/*!Draws the triangle*/
	void draw();

	/*!^INL
	@return the colour of the triangle*/
	util::vec::Vector4D& getColour();

	/*!^INL
	@col the new colour for the triangle*/
	void setColour(util::vec::Vector4D& col);

private:

	//VARIABLES
	//the colour
	util::vec::Vector4D colour;
	//the vertex coords
	VertexCoords vertexCoords;
};

//INLINE
//PUBLIC MEMBER FUNCTIONS
inline util::vec::Vector4D& TriangleCol::getColour() {

	return colour;
}

inline void TriangleCol::setColour(util::vec::Vector4D& col) {

	colour = col;
}

#endif