#include  "src/shape/triangle/TriangleCol.hpp"

//CONSTRUCTOR
TriangleCol::TriangleCol(const util::vec::Vector4D& col,
	VertexCoords& vCoords) :
	colour(col),
	vertexCoords(vCoords) {
}

//DESTRUCTOR
TriangleCol::~TriangleCol() {
}

//PUBLIC MEMBER FUNCTIONS
void TriangleCol::draw() {

	//set the colour
	glColor4f(colour.getX(), colour.getY(),
		colour.getZ(), colour.getF());

	//make sure no textures are bound
	glBindTexture(GL_TEXTURE_2D, 0);

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