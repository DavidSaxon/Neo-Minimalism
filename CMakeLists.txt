cmake_minimum_required(VERSION 2.6)
project (Neo-Minimalism)

set(SRCS
    src/display/DisplaySurface.cpp
    src/camera/Camera.cpp
    src/engine/Engine.cpp
    src/entities/level/back_ground/SpaceBox.cpp
    src/entities/level/effects/Explosion.cpp
    src/entities/level/effects/ExplosionParticle.cpp
    src/entities/level/effects/PlayerTorpedoTrail.cpp
    src/entities/level/enviroment/Asteroid.cpp
    src/entities/level/player/Player.cpp
    src/entities/level/weapons/PlayerLasor.cpp
    src/entities/level/weapons/PlayerTorpedo.cpp
    src/entities/start_up/Splash.cpp
    src/entity_list/EntityList.cpp
    src/event/Event.cpp
    src/Main.cpp
    src/renderer/Renderer.cpp
    src/resource/ResourceManager.cpp
    src/resource/types/ShapeResource.cpp
    src/resource/types/TextureResource.cpp
    src/resource/utilities/OBJLoader.cpp
    src/resource/utilities/PNGLoader.cpp
    src/shape/triangle/TriangleCol.cpp
    src/shape/triangle/TriangleTex.cpp
    src/states/level/Level.cpp
    src/states/level/Level_Event.cpp
    src/states/start_up/StartUp.cpp
    src/states/start_up/StartUp_Event.cpp
)

find_package(Boost)

set(BASEPATH "${CMAKE_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_definitions(-DBOOST_TEST_DYN_LINK)

include_directories("${BASEPATH}" ${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})

link_directories(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})

add_executable(Neo-Minimalism ${SRCS})

target_link_libraries(Neo-Minimalism
    ${Boost_LIBRARIES}

    -lboost_system
    -lboost_iostreams
    -lboost_filesystem
    -lboost_unit_test_framework
    -lGL
    -lGLU
    -lglut
    -lm
    -lpng
    -lSDL
)