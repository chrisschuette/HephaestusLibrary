/* 
 * File:   BodyDescription.cpp
 * Author: chris
 * 
 * Created on May 21, 2014, 10:29 PM
 */

#include "BodyDescription.h"
#include "../../ERR/ERR.h"

namespace PHYSICS {
    namespace BOX2D {

        BodyDescription::BodyDescription() : PHYSICS::BodyDescription() {
            m_bodyDefinition.fixedRotation = false;
            m_bodyDefinition.userData = 0;
        }

        BodyDescription::~BodyDescription() {
        }

        BodyDescription* BodyDescription::clone() const {
            return new BodyDescription(*this);
        }

        void BodyDescription::setFixedRotation(bool fixed) {
            m_bodyDefinition.fixedRotation = fixed;
        }

        bool BodyDescription::hasFixedRotation() const {
            return m_bodyDefinition.fixedRotation;
        }

        void BodyDescription::setBodyType(PHYSICS::BodyDescription::BODY_TYPE type) {
            switch (type) {
                case PHYSICS::BodyDescription::STATIC:
                    m_bodyDefinition.type = b2_staticBody;
                    break;
                case PHYSICS::BodyDescription::KINEMATIC:
                    m_bodyDefinition.type = b2_kinematicBody;
                    break;
                case PHYSICS::BodyDescription::DYNAMIC:
                    m_bodyDefinition.type = b2_dynamicBody;
                    break;
                default:
                    THROWS("Unknown body type.");
            }
        }

        void BodyDescription::setPosition(float x, float y) {
            m_bodyDefinition.position.Set(x, y);
        }

        void BodyDescription::setAngle(float angle) {
            m_bodyDefinition.angle = angle;
        }
        
        void BodyDescription::setUserData(BodyPartUserData * userData) {
            m_bodyDefinition.userData = userData;
        }
    }
}
