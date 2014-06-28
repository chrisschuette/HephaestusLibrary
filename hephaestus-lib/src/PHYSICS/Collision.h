/* 
 * File:   Collision.h
 * Author: chris
 *
 * Created on June 3, 2014, 2:18 PM
 */

#ifndef COLLISION_H
#define	COLLISION_H

namespace PHYSICS {
    class BodyPartUserData;
    class Body;
    class Collision {
    public:
        enum EVENT { BEGIN, END };
    public:
        Collision(EVENT event, Body& A, const BodyPartUserData* fixtureA, Body& B, const BodyPartUserData* fixtureB)
        : m_A(A), m_B(B)
        , m_fixtureA(fixtureA), m_fixtureB(fixtureB), m_event(event) {}
        virtual ~Collision() {}
        
        const Body& getBodyA() const { return m_A; }
        const Body& getBodyB() const { return m_B; }
        
        const BodyPartUserData* getBodyPartDataA() const { return m_fixtureA; }
        const BodyPartUserData* getBodyPartDataB() const { return m_fixtureB; }
        
        EVENT getEvent() const { return m_event; }
                
    private:
        Body& m_A;
        Body& m_B;
        const BodyPartUserData* m_fixtureA;
        const BodyPartUserData* m_fixtureB;
        EVENT m_event;
    };
}
#endif	/* COLLISION_H */

