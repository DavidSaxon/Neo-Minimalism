/************************************\
| An astroid floating through space. |
|                                    |
| @author David Saxon                |
\************************************/

#ifndef NEOMINIMALISM_ENTITIES_ENVIROMENT_ASTEROID_H_
#   define NEOMINIMALISM_ENTITIES_ENVIROMENT_ASTEROID_H_

#include "src/entity/CollisionType.hpp"
#include "src/physics/bounding/BoundingBox.hpp"

class Asteroid : public CollisionType {
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

    void collision(col::Type t);

    bool isCollisionType() const {

        return true;
    }

private:

    //VARIABLES
    //the shape for the asteroid
    SharedShape asteroid;
    //the rotation of the asteroid
    util::vec::Vector3D rot;
    //the rotation speeds of the asteroid
    util::vec::Vector3D rotSpeed;

    //CONSTRUCTOR
    DISALLOW_COPY_AND_ASSIGN(Asteroid);
};

#endif