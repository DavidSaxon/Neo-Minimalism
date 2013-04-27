/*********************************************************\
| Functions that are used for loading obj files as models |
| 														  |
| @author David Saxon									  |
\*********************************************************/

#ifndef OMICRON_RESOURCE_UTILITIES_OBJLOADER_H_
#	define OMICRON_RESOURCE_UTILITIES_OBJLOADER_H_

#include <boost/shared_ptr.hpp>
#include <fstream>
#include <stdlib.h>
#include <vector>

#include "src/Utilities/StringUtil.hpp"

#include "src/shape/Shape.hpp"
#include "src/shape/triangle/TriangleCol.hpp"
#include "src/shape/triangle/TriangleTex.hpp"

#define BUFFER_SIZE 1000

//TYPEDEFS
typedef boost::shared_ptr<Shape> SharedShape;

namespace obj_loader {

//PROTOTYPES
/*!Loads a textured shape from the given object file
@path the path name of the obj file
@tex the texture to use for the object*/
SharedShape loadOBJ(const std::string& path, GLuint tex);

/*!Loads a coloured shape from the given object file
@path the path name of the obj file
@col the colour to use for the object*/
SharedShape loadOBJ(const std::string& path, util::vec::Vector4D& col);

} //obj_loader

#endif