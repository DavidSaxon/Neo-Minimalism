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
    //title
    {
        GroupList groups;
        groups.push_back(res::START_UP);
        groups.push_back(res::LUDUM_DARE);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/start_up/title.png", groups));
        textures.insert(std::make_pair("title", t));
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
    //cross hair
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::PLAYER);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/player/cross_hair.png", groups));
        textures.insert(std::make_pair("cross_hair", t));
    }
    //player lasor
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::LASOR);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/lasors/player_lasor.png", groups));
        textures.insert(std::make_pair("player_lasor", t));
    }
    //player torpedo
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::LASOR);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/lasors/player_torpedo.png", groups));
        textures.insert(std::make_pair("player_torpedo", t));
    }
    //planet 1
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/background/planet_1.png", groups));
        textures.insert(std::make_pair("planet_1", t));
    }
    //sun
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/background/sun.png", groups));
        textures.insert(std::make_pair("sun", t));
    }
    //wall 1
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/wall/wall_1.png", groups));
        textures.insert(std::make_pair("wall_1", t));
    }
    //enemy 1
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/enemy/enemy_1.png", groups));
        textures.insert(std::make_pair("enemy_1", t));
    }
    //flyer window
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/enemy/flyer_window.png", groups));
        textures.insert(std::make_pair("flyer_window", t));
    }
    //health
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/pick_ups/health.png", groups));
        textures.insert(std::make_pair("health", t));
    }
    //missle
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/pick_ups/missle.png", groups));
        textures.insert(std::make_pair("missle", t));
    }
    //pause
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/menu/pause.png", groups));
        textures.insert(std::make_pair("pause", t));
    }
    //interceptor
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/enemy/interceptor.png", groups));
        textures.insert(std::make_pair("interceptor", t));
    }
    //interceptor window
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/enemy/interceptor_window.png", groups));
        textures.insert(std::make_pair("interceptor_window", t));
    }
    //station
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/enemy/station.png", groups));
        textures.insert(std::make_pair("station", t));
    }
    //enemy lasor
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/lasors/enemy_lasor.png", groups));
        textures.insert(std::make_pair("enemy_lasor", t));
    }
    //drone
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/enemy/drone.png", groups));
        textures.insert(std::make_pair("drone", t));
    }
    //enemy torpedo
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/lasors/enemy_torpedo.png", groups));
        textures.insert(std::make_pair("enemy_torpedo", t));
    }
    //boss body
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/enemy/boss_body.png", groups));
        textures.insert(std::make_pair("boss_body", t));
    }
    //boss arms
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedTextureRes t(new TextureResource(
            "res/gfx/tex/level/enemy/boss_arms.png", groups));
        textures.insert(std::make_pair("boss_arms", t));
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
    //title
    {
        GroupList groups;
        groups.push_back(res::START_UP);
        groups.push_back(res::OMICRON);
        groups.push_back(res::LUDUM_DARE);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/start_up/splash_large.obj",
            "title", groups));
        shapes.insert(std::make_pair("title", s));
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
    //cross hair
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::PLAYER);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/player/cross_hair.obj",
            "cross_hair", groups));
        shapes.insert(std::make_pair("cross_hair", s));
    }
    //player lasor
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::LASOR);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/lasors/player_lasor.obj",
            "player_lasor", groups));
        shapes.insert(std::make_pair("player_lasor", s));
    }
    //player torpedo
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::LASOR);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/lasors/player_torpedo.obj",
            "player_torpedo", groups));
        shapes.insert(std::make_pair("player_torpedo", s));
    }
    //player torpedo trail
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::EFFECTS);
            util::vec::Vector4D col(0.0, 1.0, 1.0, 0.6);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/lasors/player_torpedo_trail.obj",
            col, groups));
        shapes.insert(std::make_pair("player_torpedo_trail", s));
    }
    //enemy torpedo trail
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::EFFECTS);
            util::vec::Vector4D col(1.0, 0.0, 1.0, 0.6);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/lasors/player_torpedo_trail.obj",
            col, groups));
        shapes.insert(std::make_pair("enemy_torpedo_trail", s));
    }
    //player torpedo explosion particle
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::EFFECTS);
            util::vec::Vector4D col(0.0, 1.0, 1.0, 1.0);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/effects/explosion_particle_medium.obj",
            col, groups));
        shapes.insert(std::make_pair("player_torpedo_explosion_particle", s));
    }
    //player lasor explosion particle
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::EFFECTS);
            util::vec::Vector4D col(1.0, 1.0 , 0.0, 1.0);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/effects/explosion_particle_small.obj",
            col, groups));
        shapes.insert(std::make_pair("player_lasor_explosion_particle", s));
    }
    //flyer explosion
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::EFFECTS);
            util::vec::Vector4D col(1.0, 0.5, 0.0, 1.0);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/effects/explosion_particle_large.obj",
            col, groups));
        shapes.insert(std::make_pair("flyer_explosion", s));
    }
    //interceptor explosion
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::EFFECTS);
            util::vec::Vector4D col(1.0, 0.2, 0.0, 1.0);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/effects/explosion_particle_large.obj",
            col, groups));
        shapes.insert(std::make_pair("interceptor_explosion", s));
    }
    //enemy explosion
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::EFFECTS);
            util::vec::Vector4D col(1.0, 0.0, 1.0, 1.0);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/effects/explosion_particle_medium.obj",
            col, groups));
        shapes.insert(std::make_pair("enemy_torpedo_ex", s));
    }
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::EFFECTS);
            util::vec::Vector4D col(1.0, 0.5, 0.0, 1.0);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/effects/explosion_particle_large.obj",
            col, groups));
        shapes.insert(std::make_pair("player_explosion", s));
    }
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::EFFECTS);
            util::vec::Vector4D col(1.0, 0.0, 1.0, 1.0);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/effects/explosion_particle_large.obj",
            col, groups));
        shapes.insert(std::make_pair("station_explosion", s));
    }
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::EFFECTS);
            util::vec::Vector4D col(1.0, 0.0, 0.5, 1.0);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/effects/explosion_particle_large.obj",
            col, groups));
        shapes.insert(std::make_pair("drone_explosion", s));
    }
    //level fader
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::EFFECTS);
            util::vec::Vector4D col(1.0, 1.0, 1.0, 1.0);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/menu/level_fader.obj",
            col, groups));
        shapes.insert(std::make_pair("level_fader", s));
    }
    //planet 1
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/back_ground/planet_1.obj",
            "planet_1", groups));
        shapes.insert(std::make_pair("planet_1", s));
    }
    //sun
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/back_ground/sun.obj",
            "sun", groups));
        shapes.insert(std::make_pair("sun", s));
    }
    //wall 1
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/wall/wall_1.obj",
            "wall_1", groups));
        shapes.insert(std::make_pair("wall_1", s));
    }
    //wall 2
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/wall/wall_2.obj",
            "wall_1", groups));
        shapes.insert(std::make_pair("wall_2", s));
    }
    //wall 3
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/wall/wall_3.obj",
            "wall_1", groups));
        shapes.insert(std::make_pair("wall_3", s));
    }
    //wall 4
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/wall/wall_4.obj",
            "wall_1", groups));
        shapes.insert(std::make_pair("wall_4", s));
    }
    //wall end
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
            util::vec::Vector4D col(0.5, 0.5, 0.5, 1.0);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/back_ground/wall_end.obj",
            col, groups));
        shapes.insert(std::make_pair("wall_end", s));
    }
    //enemy flyer
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/enemy/enemy_flyer.obj",
            "enemy_1", groups));
        shapes.insert(std::make_pair("enemy_flyer", s));
    }
    //flyer window
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/enemy/flyer_window.obj",
            "flyer_window", groups));
        shapes.insert(std::make_pair("flyer_window", s));
    }
    //health
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/pick_ups/health.obj",
            "health", groups));
        shapes.insert(std::make_pair("health", s));
    }
    //missle
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/pick_ups/health.obj",
            "missle", groups));
        shapes.insert(std::make_pair("missle", s));
    }
    //puase
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/menu/pause.obj",
            "pause", groups));
        shapes.insert(std::make_pair("pause", s));
    }
    //interceptor
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/enemy/interceptor.obj",
            "interceptor", groups));
        shapes.insert(std::make_pair("interceptor", s));
    }
    //interceptor window
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/enemy/interceptor_window.obj",
            "interceptor_window", groups));
        shapes.insert(std::make_pair("interceptor_window", s));
    }
    //enemy lasor
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/lasors/enemy_lasor.obj",
            "enemy_lasor", groups));
        shapes.insert(std::make_pair("enemy_lasor", s));
    }
    //station
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/enemy/station.obj",
            "station", groups));
        shapes.insert(std::make_pair("station", s));
    }
    //drone
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/enemy/drone.obj",
            "drone", groups));
        shapes.insert(std::make_pair("drone", s));
    }
    //enemy torpedo
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/lasors/player_torpedo.obj",
            "enemy_torpedo", groups));
        shapes.insert(std::make_pair("enemy_torpedo", s));
    }
    //boss_body
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/enemy/boss_body.obj",
            "boss_body", groups));
        shapes.insert(std::make_pair("boss_body", s));
    }
    //boss_body
    {
        GroupList groups;
        groups.push_back(res::LEVEL);
        groups.push_back(res::BACK_GROUND);
        SharedShapeRes s(new ShapeResource(
            "res/gfx/shapes/level/enemy/boss_arms.obj",
            "boss_arms", groups));
        shapes.insert(std::make_pair("boss_arms", s));
    }
}