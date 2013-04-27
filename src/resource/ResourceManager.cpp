#include "src/resource/ResourceManager.hpp"

//CONSTRUCTOR
ResourceManager::ResourceManager() {
}

//DESTRUCTOR
ResourceManager::~ResourceManager() {
}

//PUBLIC MEMBER FUNCTIONS
void ResourceManager::init() {

	//create the textures
	createResources();
}

void ResourceManager::loadTextures() {

    //iterate over the map and load
    TextureMap::iterator
        it = textures.begin(),
        ite = textures.end();
    for (; it != ite; ++it) {

        //load
        it->second->load();
    }
}

void ResourceManager::loadTextures(res::Group group) {

    //iterate over the map and check if it's in the group
    TextureMap::iterator
        it = textures.begin(),
        ite = textures.end();
    for (; it != ite; ++it) {

        if (it->second->in(group)) {

            it->second->load();
        }
    }
}

void ResourceManager::loadShapes() {

    //iterate over the map and load
    ShapeMap::iterator
        it = shapes.begin(),
        ite = shapes.end();
    for (; it != ite; ++it) {

        //load
        if (it->second->getFillType() == res::shape::COLOURED) {

            it->second->load();
        }
        else if (it->second->getFillType() == res::shape::TEXTURED) {

            it->second->load(getTexture(it->second->getTextureTag()));
        }
    }
}

void ResourceManager::loadShapes(res::Group group) {

    //iterate over the map and check if it's in the group
    ShapeMap::iterator
        it = shapes.begin(),
        ite = shapes.end();
    for (; it != ite; ++it) {

        if (it->second->in(group)) {

            //load
            if (it->second->getFillType() == res::shape::COLOURED) {

                it->second->load();
            }
            else if (it->second->getFillType() == res::shape::TEXTURED) {

                it->second->load(getTexture(it->second->getTextureTag()));
            }
        }
    }
}

GLuint ResourceManager::getTexture(const std::string& tag) {

    return textures[tag]->get();
}

SharedShape ResourceManager::getShape(const std::string& tag) {

    return shapes[tag]->get();
}

//PRIVATE MEMBER FUNCTIONS
void ResourceManager::createResources() {

    //add textures
    //uv reference
    {

        GroupList groups;
        groups.push_back(res::ALL);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/reference/uv_map_reference.png", groups));
        textures.insert(std::make_pair("uv_map", t));
    }
    //omicron splash
    {
        GroupList groups;
        groups.push_back(res::START_UP);
        groups.push_back(res::OMICRON);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/start_up/splash_alpha_v100.png", groups));
        textures.insert(std::make_pair("omicron_splash", t));
    }
    //made for splash
    {
        GroupList groups;
        groups.push_back(res::START_UP);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/start_up/made_for.png", groups));
        textures.insert(std::make_pair("made_for_splash", t));
    }
    //ludum dare splash
    {
        GroupList groups;
        groups.push_back(res::START_UP);
        groups.push_back(res::LUDUM_DARE);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/start_up/ludum_dare.png", groups));
        textures.insert(std::make_pair("ludum_dare_splash", t));
    }
    //stars
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/background/stars_1.png", groups));
        textures.insert(std::make_pair("stars_1", t));
    }
    //asteroid 1
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::ASTEROID);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/asteroids/asteroid_1.png", groups));
        textures.insert(std::make_pair("asteroid_1", t));
    }
    //cockpit
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::PLAYER);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/player/cockpit.png", groups));
        textures.insert(std::make_pair("cockpit", t));
    }



    //add shapes
    //omicron splash
    {
        GroupList groups;
        groups.push_back(res::START_UP);
        groups.push_back(res::OMICRON);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/start_up/splash_large.obj",
            "omicron_splash", groups));
        shapes.insert(std::make_pair("omicron_splash", s));
    }
    //made for splash
    {
        GroupList groups;
        groups.push_back(res::START_UP);
        groups.push_back(res::OMICRON);
        groups.push_back(res::LUDUM_DARE);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/start_up/splash_medium.obj",
            "made_for_splash", groups));
        shapes.insert(std::make_pair("made_for_splash", s));
    }
    //ludum dare splash
    {
        GroupList groups;
        groups.push_back(res::START_UP);
        groups.push_back(res::OMICRON);
        groups.push_back(res::LUDUM_DARE);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/start_up/splash_large.obj",
            "ludum_dare_splash", groups));
        shapes.insert(std::make_pair("ludum_dare_splash", s));
    }
    //splash fader
    {
        GroupList groups;
        groups.push_back(res::START_UP);
        groups.push_back(res::OMICRON);
        groups.push_back(res::LUDUM_DARE);
        util::vec::Vector4D col(0.0, 0.0, 0.0, 1.0);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/start_up/fader.obj", col, groups));
        shapes.insert(std::make_pair("splash_fader", s));
    }
    //space box
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/back_ground/space_box.obj",
            "stars_1", groups));
        shapes.insert(std::make_pair("space_box", s));
    }
    //asteroid 1
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::ASTEROID);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/asteroids/asteroid_1.obj",
            "asteroid_1", groups));
        shapes.insert(std::make_pair("asteroid_1", s));
    }
    //cockpit
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::PLAYER);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/player/cockpit.obj",
            "cockpit", groups));
        shapes.insert(std::make_pair("cockpit", s));
    }
}