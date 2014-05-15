/* 
 * File:   Box2DBodyPart.cpp
 * Author: chris
 * 
 * Created on June 22, 2013, 1:43 AM
 */

#include "Box2DBodyPart.h"

namespace PHYSICS {
    namespace BOX2D {
Box2DBodyPart::Box2DBodyPart() : PHYSICS::BodyPart() {
    m_def.shape = &m_shape;
    m_def.density = 1.0f;
}

Box2DBodyPart::~Box2DBodyPart() {
}

void Box2DBodyPart::setDimensions(float width, float height) {
    m_shape.SetAsBox(width/2.0f, height/2.0f);
}

    }
}
