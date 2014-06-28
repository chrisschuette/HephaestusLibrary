/* 
 * File:   EntityManager.h
 * Author: chris
 *
 * Created on June 5, 2014, 9:31 AM
 */

#ifndef LVLENTITYMANAGER_H
#define	LVLENTITYMANAGER_H

#include "IEntityManager.h"
#include "../CMPN/Component.h"
#include "ADD_ENTITY.h"
#include "REMOVE_ENTITY.h"
#include "../LOG/Core.h"
#include "Context.h"

#include <list>

namespace LVL {
    class Level;

    template <class T>
    class EntityManager : public CMPN::Component<IEntityManager, T> {
    public:

        EntityManager(const CMPN::ComponentID& cid, const CMPN::ObjectID& oid)
        : CMPN::Component<IEntityManager, T>(cid, oid)
        , m_levelContext(0) {
        }

        virtual ~EntityManager() {
        }

        virtual void init(CMPN::Context& ctx) {
            m_levelContext = static_cast<LVL::Context*> (&ctx);
        }

        virtual void update(unsigned long int time, unsigned long int diff) {
            // remove first
            for (std::list<ADD_ENTITY*>::iterator i = m_addRequests.begin(), e = m_addRequests.end(); i != e; ++i) {
                addEntity(*(*i));
                delete (*i);
            }
            m_addRequests.clear();

            // then add
            for (std::list<REMOVE_ENTITY*>::iterator i = m_removeRequests.begin(), e = m_removeRequests.end(); i != e; ++i) {
                removeEntity(*(*i));
                delete (*i);
            }
            m_removeRequests.clear();
        }

        virtual void addEntity(const ADD_ENTITY& msg) = 0;
        virtual void removeEntity(const REMOVE_ENTITY& msg) = 0;

        CMPN::MessageResult handleMessage(const CMPN::MessageBase& msg) {
            switch (msg.m_MID) {
                case MID_ADD_ENTITY:
                    m_addRequests.push_back(new ADD_ENTITY(static_cast<const ADD_ENTITY&> (msg)));
                    break;
                case MID_REMOVE_ENTITY:
                    m_removeRequests.push_back(new REMOVE_ENTITY(static_cast<const REMOVE_ENTITY&> (msg)));
                    break;
            }

        }
    protected:
        LVL::Context* m_levelContext;
    private:
        std::list<ADD_ENTITY*> m_addRequests;
        std::list<REMOVE_ENTITY*> m_removeRequests;
    };
}

#endif	/* LVLENTITYMANAGER_H */

