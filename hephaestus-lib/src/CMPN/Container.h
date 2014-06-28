/* 
 * File:   Container.h
 * Author: chris
 *
 * Created on August 28, 2013, 12:53 AM
 */

#ifndef CONTAINER_H
#define	CONTAINER_H

#include "ComponentManager.h"
#include "ComponentID.h"
#include "InterfaceTypeID.h"
#include "ComponentTypeID.h"
#include "ObjectID.h"
#include "MAX.h"
#include "Implements.h"
#include "MessageBase.h"

#include <iostream>

namespace CMPN {
    
    template <class Interface>
    class Implements;
    class Context;
    class Container {
    public:
        enum CONFLICT_BEHAVIOUR {
            REPLACE,
            REJECT
        };
        
    public:
        Container();
        Container(CONFLICT_BEHAVIOUR behaviour);
        void init(Context& ctx);
        void shutdown();
        
        const ComponentID& queryInterface(InterfaceTypeID itype);
        
        template <typename Interface>
        Implements<Interface>* getComponent();
        
        const ObjectID& getObjectID() const { return m_OID; }
        
        template <typename T>
        int addComponent();
        
        template <class Interface>
        MessageResult sendMessage(const ObjectID& oid, MessageBase& msg);
        
        void destroyAllComponents();
        
        virtual ~Container();
    private:
     //   ComponentID m_interfaces[MAX_INTERFACES];
        ComponentManager& m_mgr;
        CONFLICT_BEHAVIOUR m_conflictBehaviour;
        ObjectID m_OID;
    };
        template <typename Interface>
        Implements<Interface>* Container::getComponent() {
            const ComponentID& cid = m_mgr.getComponentID(Implements<Interface>::getInterfaceTypeID(), m_OID);
            if(cid.isValid())
                return static_cast<Implements<Interface>*>(m_mgr.getComponent(cid));
            else
                return 0;
        }
        
        template <class Interface>
        MessageResult Container::sendMessage(const ObjectID& oid, MessageBase& msg) {
            const ComponentID& cid = m_mgr.getComponentID(Implements<Interface>::getInterfaceTypeID(), oid);
            if(cid.isValid()) {
                ComponentBase* component = m_mgr.getComponent(cid);
                if(component) {
                    // write on envelope
                    // this changes msg!
                    msg.Addressee = oid;
                    msg.Sender = m_OID;
                    return component->handleMessage(msg);
                }
                std::cerr << "Component invalid in container " << oid.getIndex() << std::endl;
                return MR_ERROR; // failed to deliver
            }
            std::cerr << "Failed to find an implementation of interface " << Implements<Interface>::getInterfaceTypeID()
                        << " in Container " << oid.getIndex() << std::endl;
            return MR_ERROR; // failed to deliver
        }
        
        template <typename T>
        int Container::addComponent() {
            InterfaceTypeID itype = T::getInterfaceTypeID();
            ComponentTypeID type = T::getComponentTypeID();
            const ComponentID& cid = m_mgr.createComponent(type, m_OID);
            ComponentID& old_cid = m_mgr.getComponentID(itype, m_OID);

            if(!old_cid.isValid())
                old_cid = cid;
            else {
                if(m_conflictBehaviour == REPLACE) {
                        std::cerr << "Interface " << itype << " already implemented! Replacing old component." << std::endl;
                        old_cid = cid;
                        m_mgr.destroyComponent(old_cid);
                } else if(m_conflictBehaviour == REJECT) {
                        std::cerr << "Interface " << itype << " already implemented! Rejecting new component." << std::endl;
                        m_mgr.destroyComponent(cid);
                }

            }
            return itype;
        }
}
#endif	/* CONTAINER_H */

