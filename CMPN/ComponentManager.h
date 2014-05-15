/* 
 * File:   ComponentManager.h
 * Author: chris
 *
 * Created on August 28, 2013, 12:18 AM
 */

#ifndef COMPONENTMANAGER_H
#define	COMPONENTMANAGER_H

#include "../MEM/IndexPool.h"
#include "ComponentID.h"
#include "ObjectID.h"
#include "InterfaceTypeID.h"
#include "ComponentTypeID.h"
#include "MessageResult.h"
#include "MAX.h"

namespace CMPN {
    class Container;
    class ComponentBase;
    
    template <class Interface>
    class Implements;
    
    typedef ComponentBase* (*tComponentCreator)(const ComponentID& cid);
    typedef void (*tComponentDestroyer)(ComponentBase*);
    
    struct ComponentInstanceInfo {
        ComponentInstanceInfo() : Pointer(0) {
            
        }
        ComponentTypeID Component;
        ComponentBase* Pointer;
    };
    
    struct ComponentInfo {
        InterfaceTypeID Interface;
        tComponentCreator Creator;
        tComponentDestroyer Destoyer;
    };

    class MessageBase;
    class ComponentManager {
    public:
        static ComponentManager& getInstance();
        
        const ComponentID& createComponent(const ComponentTypeID& type);
        void destroyComponent(const ComponentID& cid);
        ComponentBase* getComponent(const ComponentID& index);
        
        ObjectID registerContainer(Container* container);
        void deregisterContainer(const ObjectID& oid);
        Container* getContainer(const ObjectID& oid);
        
        InterfaceTypeID getNewInterfaceTypeID();
        InterfaceTypeID registerInterface(int subscription);
        
        ComponentTypeID registerComponentType(const InterfaceTypeID& iid, tComponentCreator c, tComponentDestroyer d);

        // Messaging
        void broadcastMessage(MessageBase& msg);
        void broadcastMessage(const InterfaceTypeID& iid, MessageBase& msg);
        MessageResult sendMessage(const InterfaceTypeID& iid, const ObjectID& oid, MessageBase& msg );
        
        // ComponentID retrieval
        ComponentID& getComponentID(const InterfaceTypeID& iid, const ObjectID& oid) {
            unsigned int iid_index = iid;
            unsigned int oid_index = oid.getIndex();
            return m_componentIDs[iid_index + MAX_INTERFACES * oid_index];
        }
        const ComponentID& getComponentID(const InterfaceTypeID& iid, const ObjectID& oid) const {
            unsigned int iid_index = iid;
            unsigned int oid_index = oid.getIndex();
            return m_componentIDs[iid_index + MAX_INTERFACES * oid_index];
        }
        
    private:
        ComponentManager();
        virtual ~ComponentManager();
        static ComponentManager* m_instancePtr;
        MEM::IndexPool m_componentIndices;
        ComponentInstanceInfo m_instanceInfos[MAX_COMPONENTS];
        ComponentInfo m_componentInfos[MAX_COMPONENT_TYPES];
        MEM::IndexPool m_containerIndices;
        Container* m_containers[MAX_CONTAINERS];
        ComponentID m_componentIDs[MAX_CONTAINERS * MAX_INTERFACES];
                
        InterfaceTypeID m_currentInterfaceTypeID;
        ComponentTypeID m_currentComponentTypeID;
        bool m_subscriptions[MAX_MESSAGE_TYPES * MAX_INTERFACES];
    };
}
#endif	/* COMPONENTMANAGER_H */

