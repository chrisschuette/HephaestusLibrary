/* 
 * File:   System.h
 * Author: chris
 *
 * Created on May 21, 2014, 7:20 PM
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#include "../MATH/vec234.h"
#include "CollisionListener.h"

namespace PHYSICS {
    class Body;
    class CollisionListener;
    class BodyDescription;
    class BoundaryCondition;
    class System {
    public:
        System(float scalingFactor);
        virtual ~System();

        virtual void update();

        virtual Body* createBody(const BodyDescription& description) = 0;
        virtual void destroyBody(PHYSICS::Body* body) = 0;
        
        virtual void setGravityVector(const MATH::vec2& g) = 0;
        
        void setCollisionListener(CollisionListener* collisionListener) {
            m_collisionListener = collisionListener;
        }
        
        void processCollisions() const {
            if(m_collisionListener)
                m_collisionListener->processCollisions();
        }
        
        void setBoundaryCondition(BoundaryCondition* boundaryCondition) {
            m_boundaryCondition = boundaryCondition;
        }
        
        float getScalingFactor() const {
            return m_scalingFactor;
        }

        void setScalingFactor(float scalingFactor) {
            m_scalingFactor = scalingFactor;
        }
        
        virtual void onResize(float width, float height);
    protected:
        float m_scalingFactor;
        CollisionListener* m_collisionListener;
        BoundaryCondition* m_boundaryCondition;
    };
}
#endif	/* SYSTEM_H */

