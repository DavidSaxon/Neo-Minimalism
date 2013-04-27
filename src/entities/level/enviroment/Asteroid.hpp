/************************************\
| An astroid floating through space. |
|                                    |
| @author David Saxon                |
\************************************/

#ifndef NEOMINIMALISM_ENTITIES_ENVIROMENT_ASTEROID_H_
#   define NEOMINIMALISM_ENTITIES_ENVIROMENT_ASTEROID_H_

#include "src/entity/Renderable.hpp"

class Asteroid : public Renderable {
public:

    //CONSTRUCTOR
    Asteroid(SharedShape s, const util::vec::Vector3D& p);

    //DESTRUCTOR
    ~Asteroid();

    //PUBLIC MEMBER FUNCTIONS
    /*!updates the asteroid*/
    void update();

    /*!renders the asteroid*/
    void render();

private:

    //VARIABLES
    //the shape for the asteroid
    SharedShape asteroid;
    //the position of the asteroid
    util::vec::Vector3D pos;
    //the rotation of the asteroid
    util::vec::Vector3D rot;
    //the rotation speeds of the asteroid
    util::vec::Vector3D rotSpeed;

    //CONSTRUCTOR
    DISALLOW_COPY_AND_ASSIGN(Asteroid);
};

#endif