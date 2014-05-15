/* 
 * File:   Box2DSystem.cpp
 * Author: chris
 * 
 * Created on June 19, 2013, 1:59 AM
 */

#include "Box2DSystem.h"
#include "Box2DBodyDefinition.h"
#include "Box2DBody.h"
#include "Box2DBodyPart.h"
#include <Box2D/Common/b2Math.h>
#include "../../ERR/ERR.h"

#define MAXBODIES 500

namespace PHYSICS {
    namespace BOX2D {

        Box2DSystem::Box2DSystem()
        : System()
        , m_referencePool(MEM::Pool< SYS::Reference< Body > >(MAXBODIES))
        , m_currentID(0) {
            m_gravity.x = 0.0f;
            m_gravity.y = -10.0f;

            m_world = new b2World(m_gravity);
        }

        Box2DSystem::Box2DSystem(const Box2DSystem& orig)
        : System(orig)
        , m_referencePool(orig.m_referencePool) {
            if (orig.m_world)
                m_world = new b2World(*orig.m_world);
            m_gravity = orig.m_gravity;
        }

        Box2DSystem::~Box2DSystem() {
            for (std::map<tID, Body*>::iterator i = m_bodies.begin(), e = m_bodies.end();
                    i != e; ++i) {
                Box2DBody* myBody = static_cast<Box2DBody*>( (*i).second );
                delete myBody;
            }
            if (m_world) {
                delete m_world;
                m_world = 0;
            }
        }

        SYS::Handle<Body> Box2DSystem::createBody(const BodyDefinition& bodyDef) {
            const Box2DBodyDefinition& def = static_cast<const Box2DBodyDefinition&> (bodyDef);
            b2Body* body = m_world->CreateBody(&def.m_def);
            Box2DBody* myBody = new Box2DBody(m_currentID, body, *this);
            // save the pointer somewhere!
            m_bodies.insert(std::pair<tID, Body*>(m_currentID, myBody));
            m_currentID++;
            return myBody->getHandle();
        }

        void Box2DSystem::attachBodyPart(SYS::Handle<Body>& body, const BodyPart& bodyPart) {
            // inject type information
            Box2DBody* myBody = static_cast<Box2DBody*> (body.operator *());
            const Box2DBodyPart& myBodyPart = static_cast<const Box2DBodyPart&> (bodyPart);
            myBody->attachBodyPart(myBodyPart);
        }

        MEM::Pool< SYS::Reference< Body > >& Box2DSystem::getReferencePool() {
            return m_referencePool;
        }

        SYS::Handle<Body> Box2DSystem::getBody(tID id) {
            std::map<PHYSICS::tID, Body*>::iterator i = m_bodies.find(id);
            if (i == m_bodies.end()) {
                L(error) << "Unknown body " << id;
                THROWS("Unable to retrieve body.");
                return SYS::Handle<Body > (0, m_referencePool);
            }
            return (*i).second->getHandle();
        }

        void Box2DSystem::showBodyInfo() {
            L(normal) << "BodyInfo:";
            for (std::map<tID, Body*>::iterator i = m_bodies.begin(), e = m_bodies.end();
                    i != e; ++i) {
                std::string type;
                switch ((*i).second->getBodyType()) {
                    case STATIC:
                        type = "STATIC";
                        break;
                    case DYNAMIC:
                        type = "DYNAMIC";
                        break;
                    default:
                        THROWS("Unknown body type.");
                }

                L(normal) << "ID: " << (*i).second->getID() << " type: " << type << " count: " << (*i).second->getReferenceCount();
            }
        }

    }
}
