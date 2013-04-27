/*****************************************\
| A resource object that holds a texture. |
|										  |
| @author David Saxon					  |
\*****************************************/

#ifndef OMICRON_RESOURCE_TYPE_TEXTURERESOURCE_H_
#	define OMICRON_RESOURCE_TYPE_TEXTURERESOURCE_H_

#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>

#include "src/Utilities/MacroUtil.hpp"

#include "src/resource/Groups.hpp"
#include "src/resource/utilities/PNGLoader.hpp"

//TYPEDEFS
typedef std::vector<res::Group> GroupList;

class TextureResource {
public:

	//CONSTRUCTOR
	/*!Creates a new texture resource
	@filename the path where the texture is located
	@g the list of groups the texture is in*/
	TextureResource(const std::string& filename, GroupList& g);

	//DESTRUCTOR
	~TextureResource();

	//PUBLIC MEMBER FUNCTIONS
	/*!Loads the texture into memory*/
	void load();

	/*!@return true if the texture is within the group
	@group the group to check if this is within*/
	bool in(res::Group group) const;

	/*!^INL
	@return the texture*/
	GLuint get() const;

private:

	//VARIABLES
	//the path where the texture is located
	std::string path;
	//the texture
	GLuint tex;
	//the list of groups the texture is in
	GroupList groups;

	//CONSTRUCTOR
	DISALLOW_COPY_AND_ASSIGN(TextureResource);
};

//INLINE
//PUBLIC MEMBER FUNCTIONS
inline GLuint TextureResource::get() const {

	return tex;
}

#endif