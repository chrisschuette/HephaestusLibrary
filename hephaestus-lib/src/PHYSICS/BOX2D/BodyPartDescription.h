/* 
 * File:   BodyPartDescription.h
 * Author: chris
 *
 * Created on May 21, 2014, 11:37 PM
 */

#ifndef BOX2DBODYPARTDESCRIPTION_H
#define	BOX2DBODYPARTDESCRIPTION_H

#include "../BodyPartDescription.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "../../MATH/vec234.h"

#include <list>

namespace PHYSICS {
    class BodyPartUserData;
    namespace BOX2D {
        class BodyPartDescription : public PHYSICS::BodyPartDescription {
        public:
            BodyPartDescription();
            virtual ~BodyPartDescription();

            const b2FixtureDef* getBox2DDescription() const {
                return &m_description;
            }

            virtual BodyPartDescription* clone() const;
            
            void setDimensions(float halfWidth, float halfHeight);
            void setPolygonShape(const std::list<MATH::vec2>& outline);
            void setSensor(bool sensor);
            void setUserData(BodyPartUserData* userData) {
                m_description.userData = userData;
            }
            
        private:
            b2FixtureDef m_description;
            b2PolygonShape m_shape;
        };
    }
}
#endif	/* BOX2DBODYPARTDESCRIPTION_H */

