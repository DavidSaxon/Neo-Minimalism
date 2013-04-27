#include "src/resource/types/TextureResource.hpp"

//CONSTRUCTOR
TextureResource::TextureResource(const std::string& filename, GroupList& g) :
	path(filename),
    groups(g),
	tex(0) {
}

//DESTRUCTOR
TextureResource::~TextureResource() {
}

//PUBLIC MEMBER FUNCTIONS
void TextureResource::load() {

	//create a byte array for the image
    GLubyte* img;

    //placeholder variables
    int width;
    int height;
    bool hasAlpha;  
    
    //perform loading and texture generation
    png_loader::loadPNG((char*) path.c_str(), width, height, hasAlpha, &img);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, img);
}

bool TextureResource::in(res::Group group) const {

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