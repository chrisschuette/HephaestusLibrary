/* 
 * File:   Body.h
 * Author: chris
 *
 * Created on May 21, 2014, 7:45 PM
 */

#ifndef BOX2DBODY_H
#define	BOX2DBODY_H

#include "../Body.h"
#include <Box2D/Dynamics/b2Body.h>

namespace PHYSICS {
    namespace BOX2D {
        class System;

        class Body : public PHYSICS::Body {
            friend class System;
        public:
            virtual ~Body();
            virtual void createBodyPart(const PHYSICS::BodyPartDescription& description);
            virtual std::list<MATH::vec4> getBoundingBox() const;
            virtual void applyLinearImpulse(const MATH::vec2& F);
            virtual void applyLinearImpulse(float px, float py);
            virtual void applyForce(float fx, float fy);

            virtual void applyAngularMomentum(float f);
            virtual const MATH::vec2& getPosition() const;
            virtual float getOrientation() const;

            virtual const MATH::vec2& getVelocity() const;
            virtual float getAngularVelocity() const;

            virtual float getMass() const;
            virtual float getMomentOfInertia() const;

            virtual std::list< std::pair< int, MATH::vec2* > > getBodyPartShapes() const;
            virtual std::list<GEOMETRY::Polygon> getBodyPartPolygons() const;

        protected:
            Body(b2Body* body, PHYSICS::System& world);

            b2Body* getBox2DBody() {
                return m_body;
            }
        private:
            b2Body* m_body;
        };
    }
}
#endif	/* BOX2DBODY_H */

