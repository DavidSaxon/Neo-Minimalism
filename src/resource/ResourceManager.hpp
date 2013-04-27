/**************************************************\
| Manages the access and loading of all resources. |
|												   |
| @author David Saxon							   |
\**************************************************/

#ifndef OMICRON_RESOURCE_RESOURCEMANAGER_H_
#	define OMICRON_RESOURCE_RESOURCEMANAGER_H_

#include <boost/shared_ptr.hpp>
#include <map>

#include "src/resource/Groups.hpp"
#include "src/resource/types/ShapeResource.hpp"
#include "src/resource/types/TextureResource.hpp"

//TYPEDEFS
typedef boost::shared_ptr<ShapeResource> SharedShapeRes;
typedef boost::shared_ptr<TextureResource> SharedTextureRes;
typedef std::map<std::string, SharedShapeRes> ShapeMap;
typedef std::map<std::string, SharedTextureRes> TextureMap;

class ResourceManager {
public:

	//CONSTRUCTOR
	/*!Creates a new resource manager*/
	ResourceManager();

	//DESTRUCTOR
	/*!Destroys the resource manager*/
	~ResourceManager();

	//PUBLIC MEMBER FUNCTIONS
	/*!Initialises the resource manager*/
	void init();

	/*!Loads all of the textures into memory*/
	void loadTextures();

	/*!Loads all of the textures within the group into memory
	@group the resource group*/
	void loadTextures(res::Group group);

	/*!Loads all of the shapes into memory*/
	void loadShapes();

	/*!Loads all of the shapes within the group into memory
	@group the resource group*/
	void loadShapes(res::Group group);

	/*!Get the texture associated with the given tag
	@tag the resource tag
	@return the texture*/
	GLuint getTexture(const std::string& tag);

	/*!Get the shape associated with the given tag
	@tag the resource tag
	@return the shape*/
	SharedShape getShape(const std::string& tag);

private:

	//VARIABLES
	//the map of textures
	TextureMap textures;
	//the map of shapes
	ShapeMap shapes;

	//CONSTRUCTOR
	DISALLOW_COPY_AND_ASSIGN(ResourceManager);

	//PRIVATE MEMBER FUNCTIONS
	/*!creates all the resources*/
	void createResources();
};

#endif