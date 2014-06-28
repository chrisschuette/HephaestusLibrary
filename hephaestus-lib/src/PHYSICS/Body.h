/* 
 * File:   Body.h
 * Author: chris
 *
 * Created on May 21, 2014, 7:41 PM
 */

#ifndef BODY_H
#define	BODY_H

#include "../MATH/vec234.h"
#include "../GEOMETRY/Polygon.h"

#include <list>

namespace PHYSICS {
    class System;
    class BodyPartDescription;
    class BodyUserData;
    class Body {
    public:
        virtual ~Body();
        virtual const MATH::vec2& getPosition() const = 0;
        virtual float getOrientation() const = 0;
        virtual void createBodyPart( const BodyPartDescription& description ) = 0;
        virtual std::list<MATH::vec4> getBoundingBox() const = 0;
        virtual void applyLinearImpulse( const MATH::vec2& F ) = 0;
        virtual void applyLinearImpulse( float px, float py ) = 0;
        virtual void applyForce(float fx, float fy ) = 0;
        virtual void applyAngularMomentum( float f ) = 0;
        
        virtual const MATH::vec2& getVelocity() const = 0;
        virtual float getAngularVelocity() const = 0;
        
        virtual float getMass() const = 0;
        virtual float getMomentOfInertia() const = 0;

        virtual System& getWorld() { return m_world; }

        virtual std::list< std::pair< int, MATH::vec2* > > getBodyPartShapes() const = 0;
        virtual std::list<GEOMETRY::Polygon> getBodyPartPolygons() const = 0;
        
        // user data
        const BodyUserData* getUserData() const { return m_userData; }
        void setUserData(BodyUserData* userData) { m_userData = userData; }
    protected:
        Body(System& world);
        System& m_world;
        BodyUserData* m_userData;
    };
}
#endif	/* BODY_H */

