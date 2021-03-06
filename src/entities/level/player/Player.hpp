/*********************\
| The player          |
|                     |
| @author David Saxon |
\*********************/

#ifndef NEOMINIMALISM_ENTITIES_LEVEL_PLAYER_PLAYER_H_
#   define NEOMINIMALISM_ENTITIES_LEVEL_PLAYER_PLAYER_H_

#include <cmath>

#include "src/Utilities/ValuesUtil.hpp"

#include "src/entity/CollisionType.hpp"
#include "src/physics/bounding/BoundingBox.hpp"

class Player : public CollisionType {
public:

    //VARIABLES
    //the max speed of the player
    const float maxSpeed;
    bool torpedo;
    bool dead;

    //CONSTRUCTOR
    Player(SharedShape c, SharedShape h, SharedShape f);

    //DESTRUCTOR
    ~Player();

    //PUBLIC MEMBER FUNCTIONS
    /*!updates the player*/
    void update();

    /*!Renders the player*/
    void render();

    /*!Renders transparent shapes*/
    void renderTransparent();

    /*!^INL
    @return the position of the player*/
    util::vec::Vector3D getPos();

    util::vec::Vector3D& getRot();

    void noTurn();

    /*!turns the player to the left*/
    void turnLeft();

    /*!turns the player to the right*/
    void turnRight();

    void collision(col::Type t);

    bool isCollisionType() const {

        return true;
    }

private:

    //VARIABLES
    //the shape for the cockpit
    SharedShape cockpit;
    //the shape for the cross hairs
    SharedShape crossHair;
    SharedTriangleCol fader;

    //the rotation of the player
    util::vec::Vector3D rot;

    //the current speed of the player
    float currentSpeed;
    //the speed in which the player can move side ways
    float turnSpeed;
    float tiltAngle;
    float tiltSpeed;
    //the direction the player is turning
    unsigned turnDir;

    int health;
    int maxHealth;

    unsigned torpedoTime;
    int torpedoCounter;

    float fade;

    //CONSTRUCTOR
    DISALLOW_COPY_AND_ASSIGN(Player);

    //PRIVATE MEMBER FUNCTIONS
    void move();

    void tilt();
};

//INLINE
//PUBLIC MEMBER FUNCTIONS
inline util::vec::Vector3D Player::getPos() {

    return pos;
}

inline util::vec::Vector3D& Player::getRot() {

    return rot;
}

#endif