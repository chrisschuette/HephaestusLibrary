#include "CollisionListener.h"
#include "Collision.h"
#include "../LOG/Core.h"

#define NAME "CollisionListener"

namespace PHYSICS {

    CollisionListener::~CollisionListener() {
        for (std::list<Collision*>::iterator i = m_collisions.begin(), e = m_collisions.end(); i != e; ++i)
            delete (*i);
    }

    void CollisionListener::processCollisions() {
        for (std::list<Collision*>::iterator i = m_collisions.begin(), e = m_collisions.end(); i != e; ++i) {
            processCollision(*(*i));
            delete (*i);
        }
        m_collisions.clear();
    }
}