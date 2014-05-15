/* 
 * File:   Box2DBody.cpp
 * Author: chris
 * 
 * Created on June 19, 2013, 2:03 AM
 */

#include <Box2D/Dynamics/b2World.h>

#include "Box2DBody.h"
#include "Box2DBodyDefinition.h"
#include "Box2DSystem.h"
#include "Box2DBodyPart.h"
#include "../../ERR/ERR.h"

namespace PHYSICS {
    namespace BOX2D {
Box2DBody::Box2DBody(tID ID, b2Body* body/*, const Box2DBodyDefinition& definition*/, Box2DSystem& system)
: PHYSICS::Body(ID/*, definition*/, system)
, m_body(body) {
}

Box2DBody::~Box2DBody() {
}

int Box2DBody::getBodyType() const {
    switch(m_body->GetType()) {
        case b2_staticBody:
            return PHYSICS::STATIC;
            break;
        case b2_dynamicBody:
            return PHYSICS::DYNAMIC;
            break;
        default:
            THROWS("Unknown body type.");
    }
}

 void Box2DBody::attachBodyPart(const Box2DBodyPart& bodyPart) {
     m_body->CreateFixture(bodyPart.getPartDefinition());
 }

    
    }
}
