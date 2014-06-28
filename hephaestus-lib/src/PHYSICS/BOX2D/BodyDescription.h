/* 
 * File:   BodyDescription.h
 * Author: chris
 *
 * Created on May 21, 2014, 10:29 PM
 */

#ifndef BOX2DBODYDESCRIPTION_H
#define	BOX2DBODYDESCRIPTION_H

#include "../BodyDescription.h"
#include <Box2D/Dynamics/b2Body.h>

namespace PHYSICS {
    class BodyPartUserData;
    namespace BOX2D {

        class BodyDescription : public PHYSICS::BodyDescription {
        public:
            BodyDescription();
            virtual ~BodyDescription();

            virtual BodyDescription* clone() const;

            
            // implementation setters
            virtual void setBodyType(BODY_TYPE type);
            virtual void setPosition(float x, float y);
            virtual void setAngle(float angle);
            void setFixedRotation(bool fixed);
            bool hasFixedRotation() const;
            
            void setUserData(BodyPartUserData * userData);
            
            const b2BodyDef* getBox2DDefinition() const { return &m_bodyDefinition; }
        private:
            b2BodyDef m_bodyDefinition;
        };
    }
}
#endif	/* BOX2DBODYDESCRIPTION_H */

