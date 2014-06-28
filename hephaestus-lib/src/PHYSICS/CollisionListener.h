/* 
 * File:   CollisionListener.h
 * Author: chris
 *
 * Created on June 3, 2014, 2:16 PM
 */

#ifndef COLLISIONLISTENER_H
#define	COLLISIONLISTENER_H

#include <list>

namespace PHYSICS {
    class Collision;
    class CollisionListener {
    public:
        CollisionListener() {}
        virtual ~CollisionListener();
        
        void queueCollision(Collision* collision) {
            m_collisions.push_back(collision);
        }
        void processCollisions();
    private:
        virtual void processCollision(const Collision& collision) = 0;
        std::list<Collision*> m_collisions;
    };
}
#endif	/* COLLISIONLISTENER_H */

