/**************************\
| The sky-box in the level |
|                          |
| @author David Saxon      |
\**************************/

#ifndef NEOMINIMALISM_ENTITIES_LEVEL_BACKGROUND_SPACEBOX_H_
#   define NEOMINIMALISM_ENTITIES_LEVEL_BACKGROUND_SPACEBOX_H_

#include "src/entity/Renderable.hpp"

class SpaceBox : public Renderable {
public:

    //CONSTRUCTOR
    SpaceBox(SharedShape s);

    //DESTRUCTOR
    ~SpaceBox();

    //PUBLIC MEMBER FUNCTIONS
    /*!updates the spacebox*/
    void update();

    /*!renders the space box*/
    void render();

    /*!sets the position of the space box*/
    void setPos(const util::vec::Vector3D& p);

private:

    //VARIABLES
    //the space box
    SharedShape box;

    //CONSTRUCTOR
    DISALLOW_COPY_AND_ASSIGN(SpaceBox);
};

//INLINE
//PUBLIC MEMBER FUNCTIONS
inline void SpaceBox::setPos(const util::vec::Vector3D& p) {

    pos = p;
}

#endif