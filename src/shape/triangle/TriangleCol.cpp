#include  "src/shape/triangle/TriangleCol.hpp"

//CONSTRUCTOR
TriangleCol::TriangleCol(const util::vec::Vector4D& col,
	VertexCoords& vCoords) :
	vertexCoords(vCoords) {

	colour.setX(col.getX());
	colour.setY(col.getY());
	colour.setZ(col.getZ());
	colour.setF(col.getF());
}

//DESTRUCTOR
TriangleCol::~TriangleCol() {
}

//PUBLIC MEMBER FUNCTIONS
void TriangleCol::draw() {

	//make sure no textures are bound
	glBindTexture(GL_TEXTURE_2D, 0);

	//set the colour
	glColor4f(colour.getX(), colour.getY(),
		colour.getZ(), colour.getF());

	//start drawing triangles
	glBegin(GL_TRIANGLES);

	//iterate over the vertex coorsd and draw them
	VertexCoords::const_iterator
		it = vertexCoords.begin(),
		ite = vertexCoords.end();
	for(; it != ite; ++it) {

		glVertex3f((*it)->getX(), (*it)->getY(), (*it)->getZ());
	}

	glEnd();
}