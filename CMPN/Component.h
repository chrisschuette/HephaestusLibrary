/* 
 * File:   Component.h
 * Author: chris
 *
 * Created on August 28, 2013, 12:41 AM
 */

#ifndef COMPONENT_H
#define	COMPONENT_H

#include "ComponentTypeID.h"
#include "InterfaceTypeID.h"
#include "Implements.h"

namespace CMPN {
    template <class Interface, class Implementation>
    class Component : public Implements<Interface> {
    public:
        Component(const ComponentID& cid) : Implements<Interface>(cid) {
            (void)&m_CTID;
        }
        virtual ~Component() {
        }
        
        static ComponentBase* create(const ComponentID& cid) { return new Implementation(cid); }
        static void destroy(ComponentBase* component) { delete static_cast<Implementation*>(component); }
        
        static const ComponentTypeID& getComponentTypeID() { return m_CTID; }
    private:
        static ComponentTypeID m_CTID;
    };
#include "ComponentManager.h"
        template <class Interface, class Implementation> ComponentTypeID Component<Interface,Implementation>::m_CTID = 
                ComponentManager::getInstance().registerComponentType(Implements<Interface>::getInterfaceTypeID(), &Component::create,
                                                                             &Component::destroy);
}

#endif	/* COMPONENT_H */

