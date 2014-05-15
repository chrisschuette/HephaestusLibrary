/* 
 * File:   Box2DBodyDefinition.cpp
 * Author: chris
 * 
 * Created on June 19, 2013, 2:06 AM
 */

#include "Box2DBodyDefinition.h"
#include "Box2DOrientation.h"
#include "Box2DPosition.h"
#include "../../ERR/ERR.h"

namespace PHYSICS {
    namespace BOX2D {

        Box2DBodyDefinition::Box2DBodyDefinition() : PHYSICS::BodyDefinition() {
        }

        Box2DBodyDefinition::~Box2DBodyDefinition() {
        }

        void Box2DBodyDefinition::setOrientation(const Orientation& orientation) {
            const Box2DOrientation& orient = static_cast<const Box2DOrientation&> (orientation);
            m_def.angle = orient;
        }

        void Box2DBodyDefinition::setPosition(const Position& position) {
            const Box2DPosition& pos = static_cast<const Box2DPosition&> (position);
            m_def.position = pos;
        }
        
        void Box2DBodyDefinition::setBodyType(BODY_TYPE type) {
            switch(type) {
                case PHYSICS::STATIC:
                    m_def.type = b2_staticBody;
                    break;
                case PHYSICS::DYNAMIC:
                    m_def.type = b2_dynamicBody;
                    break;
                default:
                    THROWS("Unknown body type");
            }
        }

    }
}
