/*********************\
| The player          |
|                     |
| @author David Saxon |
\*********************/

#ifndef NEOMINIMALISM_ENTITIES_LEVEL_PLAYER_PLAYER_H_
#   define NEOMINIMALISM_ENTITIES_LEVEL_PLAYER_PLAYER_H_

#include <cmath>

#include "src/Utilities/ValuesUtil.hpp"

#include "src/entity/Renderable.hpp"

class Player : public Renderable {
public:

    //VARIABLES
    //the max speed of the player
    const float maxSpeed;

    //CONSTRUCTOR
    Player(SharedShape c);

    //DESTRUCTOR
    ~Player();

    //PUBLIC MEMBER FUNCTIONS
    /*!updates the player*/
    void update();

    /*!Renders the player*/
    void render();

    /*!^INL
    @return the position of the player*/
    util::vec::Vector3D& getPos();

    /*!^INL
    @return the tilt rotation of the player*/
    util::vec::Vector3D getTiltRot();

    /*!^INL
    @return the turn rotation of the player*/
    util::vec::Vector3D getTurnRot();

    /*!turns the player up*/
    void turnUp();

    /*!turns the player down*/
    void turnDown();

    /*!turns the player to the left*/
    void turnLeft();

    /*!turns the player to the right*/
    void turnRight();

private:

    //VARIABLES
    //the shape for the cockpit
    SharedShape cockpit;

    //the position of the player
    util::vec::Vector3D pos;
    //the turn rotation of the player
    util::vec::Vector3D turnRot;
    //the tilt rotation of the player
    util::vec::Vector3D tiltRot;

    //the turn speed
    float turnSpeed;

    //the current speed of the player
    float currentSpeed;

    //CONSTRUCTOR
    DISALLOW_COPY_AND_ASSIGN(Player);

    //PRIVATE MEMBER FUNCTIONS
    void move();
};

//INLINE
//PUBLIC MEMBER FUNCTIONS
inline util::vec::Vector3D& Player::getPos() {

    return pos;
}

inline util::vec::Vector3D Player::getTiltRot() {

    return tiltRot;
}

inline util::vec::Vector3D Player::getTurnRot() {

    return turnRot;
}

#endif