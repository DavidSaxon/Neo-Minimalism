#include "src/resource/types/ShapeResource.hpp"

//CONSTRUCTORS
ShapeResource::ShapeResource(const std::string& filename,
	util::vec::Vector4D& col, GroupList& g) :
	path(filename),
	groups(g),
	fill(res::shape::COLOURED),
	colour(col) {
}

ShapeResource::ShapeResource(const std::string& filename,
	const std::string& tex, GroupList& g) :
	path(filename),
	groups(g),
	fill(res::shape::TEXTURED),
	texture(tex) {
}

//DESTRUCTOR
ShapeResource::~ShapeResource() {
}

//PUBLIC MEMBER FUNCTIONS
void ShapeResource::load() {

    shape = obj_loader::loadOBJ(path, colour);
}

void ShapeResource::load(GLuint tex) {

	shape = obj_loader::loadOBJ(path, tex);
}

bool ShapeResource::in(res::Group group) const {

    //iterate over the groups this in and check if it is the group
    GroupList::const_iterator
        it = groups.begin(),
        ite = groups.end();
    for (; it != ite; ++it) {

        //has been found
        if (*it == group) {

            return true;
        }
    }

    //not in the group
    return false;
}