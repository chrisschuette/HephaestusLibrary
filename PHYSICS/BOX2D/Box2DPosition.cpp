/* 
 * File:   Box2DPosition.cpp
 * Author: chris
 * 
 * Created on June 21, 2013, 5:31 PM
 */

#include "Box2DPosition.h"

namespace PHYSICS {
    namespace BOX2D {
Box2DPosition::Box2DPosition()
: PHYSICS::Position()
{
}

Box2DPosition::Box2DPosition(float x, float y)
: PHYSICS::Position()
, m_position(b2Vec2(x,y))
{
    
}


Box2DPosition::~Box2DPosition() {
}

    void Box2DPosition::set(float x, float y) {
        m_position = b2Vec2(x,y);
    }

    }
}
