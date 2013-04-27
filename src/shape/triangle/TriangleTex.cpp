#include "src/shape/triangle/TriangleTex.hpp"

//CONSTRUCTOR
TriangleTex::TriangleTex(GLuint tex, VertexCoords& vCoords,
	TexCoords& tCoords) :
	texture(tex),
	vertexCoords(vCoords),
	texCoords(tCoords) {
}

//DESTRUCTOR
TriangleTex::~TriangleTex() {
}

//PUBLIC MEMBER FUNCTIONS
void TriangleTex::draw() {

	//set the colour to white and bind the texture
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texture);

	//start drawing triangles
	glBegin(GL_TRIANGLES);

	//iterate over the vertex coorsd and draw them
	for(unsigned i = 0; i < vertexCoords.size(); ++i) {

		//set the texture coords
		glTexCoord2f(texCoords[i]->getX(), texCoords[i]->getY());

		//draw the vertices
		glVertex3f(vertexCoords[i]->getX(),
			vertexCoords[i]->getY(), vertexCoords[i]->getZ());
	}

	glEnd();
}