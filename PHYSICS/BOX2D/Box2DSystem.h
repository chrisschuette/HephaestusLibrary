/* 
 * File:   Box2DSystem.h
 * Author: chris
 *
 * Created on June 19, 2013, 1:59 AM
 */

#ifndef BOX2DSYSTEM_H
#define	BOX2DSYSTEM_H

#include "../System.h"
#include <Box2D/Dynamics/b2World.h>
#include <map>

namespace PHYSICS {
    namespace BOX2D {
        class Box2DBody;
class Box2DSystem: public PHYSICS::System {
public:
    Box2DSystem();
    Box2DSystem(const Box2DSystem& orig);
    virtual SYS::Handle<Body> createBody(const BodyDefinition& bodyDef);
    virtual void attachBodyPart(SYS::Handle<Body>& body, const BodyPart& bodyPart);

    virtual MEM::Pool< SYS::Reference< Body > >& getReferencePool();
    b2World* getWorldPtr() { return m_world; }
    SYS::Handle<Body> getBody(tID id);
    virtual void showBodyInfo();

    virtual ~Box2DSystem();
private:
    MEM::Pool< SYS::Reference< Body > > m_referencePool;
    b2Vec2 m_gravity;
    b2World* m_world;
    std::map<PHYSICS::tID, Body*> m_bodies;
    tID m_currentID;

};
    }
}
#endif	/* BOX2DSYSTEM_H */

