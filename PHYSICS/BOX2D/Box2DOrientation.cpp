/* 
 * File:   Box2DOrientation.cpp
 * Author: chris
 * 
 * Created on June 21, 2013, 5:35 PM
 */

#include "Box2DOrientation.h"

namespace PHYSICS {
    namespace BOX2D {
Box2DOrientation::Box2DOrientation()
: PHYSICS::Orientation()
, m_angle(0.0f)
{
}

Box2DOrientation::Box2DOrientation(float angle)
: PHYSICS::Orientation()
, m_angle(angle)
{
    
}


Box2DOrientation::~Box2DOrientation() {
}
    }
}
