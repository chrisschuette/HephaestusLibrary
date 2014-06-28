/* 
 * File:   Implements.h
 * Author: chris
 *
 * Created on August 28, 2013, 1:46 AM
 */

#ifndef IMPLEMENTS_H
#define	IMPLEMENTS_H

#include "InterfaceTypeID.h"
#include "ComponentBase.h"
#include "ComponentID.h"
#include "MessageResult.h"
#include "ComponentManager.h"

namespace CMPN {
template<typename Interface>
class Implements: public Interface, public ComponentBase {
    public:
        Implements(const ComponentID& cid, const ObjectID& oid) : ComponentBase(cid, oid), Interface() {}
        virtual ~Implements() {}
        static const InterfaceTypeID& getInterfaceTypeID() { return m_ITID; }
    protected:
        static InterfaceTypeID m_ITID;
};

template <class Interface>
InterfaceTypeID
Implements<Interface>::m_ITID = ComponentManager::getInstance().registerInterface(Interface::subscriptions);

}
#endif	/* IMPLEMENTS_H */

