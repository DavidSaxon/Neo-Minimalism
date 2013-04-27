/***************************************\
| A Resource object that holds a shape. |
|										|
| @author David Saxon					|
\***************************************/

#ifndef OMICRON_RESOURCE_TYPES_SHAPERESOURCE_H_
#	define OMICRON_RESOURCE_TYPES_SHAPERESOURCE_H_

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <vector>

#include "src/Utilities/MacroUtil.hpp"
#include "src/Utilities/vector/Vector4D.hpp"

#include "src/resource/Groups.hpp"
#include "src/resource/utilities/OBJLoader.hpp"
#include "src/shape/Shape.hpp"

//TYPEDEFS
typedef boost::shared_ptr<Shape> SharedShape;
typedef std::vector<res::Group> GroupList;

namespace res { namespace shape {

enum FillType {

	COLOURED = 0,
	TEXTURED
};

} } //res //shape

class ShapeResource {
public:

	//CONSTRUCTORS
	/*!Creates a new coloured shape resource
	@filename the file path to the shape
	@col the colour of the shape
	@g the groups the resource is in*/
	ShapeResource(const std::string& filename,
		util::vec::Vector4D& col, GroupList& g);

	/*!Creates a new textured shape resource
	@filename the file path to the shape
	@tex the resource tag of the texture
	@g the groups the resource is in*/
	ShapeResource(const std::string& filename,
		const std::string& tex, GroupList& g);

	//DESTRUCTOR
	/*!Destroys the shape resource*/
	~ShapeResource();

	//PUBLIC MEMBER FUNCTIONS
	/*!Loads the coloured shape into memory*/
	void load();

	/*!Loads the textured shape into memory
	@the texture to use for the shape*/
	void load(GLuint tex);

	/*!@return true if shape resource is wihtin the group
	@group the group to check if this is within*/
	bool in(res::Group group) const;

	/*!^INL
	@return the shape*/
	SharedShape get() const;

	/*!^INL
	@return the fill type of the shape*/
	res::shape::FillType getFillType() const;

	/*!^INL
	@return the texture tag for the shape*/
	std::string getTextureTag() const;

private:

	//VARIABLES
	//the path where the shape is located
	std::string path;
	//the shape
	SharedShape shape;
	//the list of groups the shape is in
	GroupList groups;

	//the fill type of the shape
	res::shape::FillType fill;

	//the texture tag of the shape
	std::string texture;
	//the colour of the shape
	util::vec::Vector4D colour;

	//CONSTRUCTOR
	DISALLOW_COPY_AND_ASSIGN(ShapeResource);
};

//INLINE
//PUBLIC MEMBER FUNCTIONS
inline SharedShape ShapeResource::get() const {

	return shape;
}

inline res::shape::FillType ShapeResource::getFillType() const {

	return fill;
}


inline std::string ShapeResource::getTextureTag() const {

	return texture;
}

#endif