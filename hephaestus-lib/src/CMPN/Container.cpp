/* 
 * File:   Container.cpp
 * Author: chris
 * 
 * Created on August 28, 2013, 12:53 AM
 */

#include "Container.h"
#include "ComponentManager.h"
#include "Context.h"
#include <cstring>

namespace CMPN {

    Container::Container()
    : m_mgr(ComponentManager::getInstance()), m_OID(m_mgr.registerContainer(this))
    , m_conflictBehaviour(REPLACE) {
    }
    
    Container::Container(CONFLICT_BEHAVIOUR behaviour)
    : m_mgr(ComponentManager::getInstance()), m_OID(m_mgr.registerContainer(this))
    , m_conflictBehaviour(behaviour) {
    }

    Container::~Container() {
        shutdown();
    }

    void Container::init(Context& ctx) {
        for (int i = 0; i < MAX_INTERFACES; i++) {
            const InterfaceTypeID itype(i);
            const ComponentID& cid = m_mgr.getComponentID(itype, m_OID);
            if (cid.isValid())
                m_mgr.getComponent(cid)->init(ctx);
        }
    }

    void Container::shutdown() {
        destroyAllComponents();
        m_mgr.deregisterContainer(m_OID);
    }

    const ComponentID& Container::queryInterface(InterfaceTypeID itype) {
        return m_mgr.getComponentID(itype, m_OID);
    }

    void Container::destroyAllComponents() {
        for (int i = 0; i < MAX_INTERFACES; i++) {
            const InterfaceTypeID itype(i);
            const ComponentID& cid = m_mgr.getComponentID(itype, m_OID);
            if (cid.isValid()) {
                m_mgr.destroyComponent(cid);
            }
        }
    }


}
