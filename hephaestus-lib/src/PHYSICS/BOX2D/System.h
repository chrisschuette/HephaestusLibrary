/* 
 * File:   System.h
 * Author: chris
 *
 * Created on May 21, 2014, 7:23 PM
 */

#ifndef BOX2DSYSTEM_H
#define	BOX2DSYSTEM_H

#include "../System.h"
#include <Box2D/Dynamics/b2World.h>

namespace PHYSICS {
    namespace BOX2D {
        class Body;
        class System: public PHYSICS::System, b2ContactListener {
            friend class Body;
        public:
            System(float scalingFactor);
            virtual ~System();
            
            virtual void update();
            virtual PHYSICS::Body* createBody(const PHYSICS::BodyDescription& description);
            virtual void setGravityVector(const MATH::vec2& g);
            virtual void BeginContact(b2Contact* contact);
            virtual void EndContact(b2Contact* contact);
            b2World& getBox2DWorld() { return m_world; }
        private:
            virtual void destroyBody(PHYSICS::Body* body);
            b2World m_world;
            
            float m_timeStep;
            int m_velocityIterations;
            int m_positionIterations;
            int stepsPerUpdate;
            
        };
    }
}
#endif	/* BOX2DSYSTEM_H */

