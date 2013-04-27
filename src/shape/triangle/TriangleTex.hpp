/********************************\
| Represents a textured triangle |
|								 |
| @author David Saxon			 |
\********************************/

#ifndef OMICRON_SHAPE_TRIANGLE_TRIANGLETEX_H_
#	define OMICRON_SHAPE_TRIANGLE_TRIANGLETEX_H_

#include <iostream>

#include "src/shape/Shape.hpp"

class TriangleTex : public Shape {
public:

	//CONSTRUCTOR
	/*!Creates a new textured triangle
	@tex the texture of the triangle
	@vCoords the vertex co-ordinates of the triangle
	@tCoords the texture co-ordinates of the triangle*/
	TriangleTex(GLuint tex, VertexCoords& vCoords, TexCoords& tCoords);

	//DESTRUCTOR
	/*!Destroys the triangle*/
	~TriangleTex();

	//PUBLIC MEMBER FUNCTIONS
	/*!Draws the triangle*/
	void draw();

private:

	//VARIABLES
	//the texture
	GLuint texture;
	//the vertex coords
	VertexCoords vertexCoords;
	//the texture coords
	TexCoords texCoords;
};

#endif