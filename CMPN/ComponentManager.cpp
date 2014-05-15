/* 
 * File:   ComponentManager.cpp
 * Author: chris
 * 
 * Created on August 28, 2013, 12:18 AM
 */
#include "ComponentManager.h"

#include "ComponentBase.h"
#include "Container.h"

#include "example/ITest.h"
#include "Implements.h"
#include "Component.h"

#include <cmath>
#include <cstring>

namespace CMPN {

    ComponentManager* ComponentManager::m_instancePtr(0);

    ComponentManager::ComponentManager()
    : m_componentIndices(MAX_COMPONENTS)
    , m_containerIndices(MAX_CONTAINERS)
    , m_currentInterfaceTypeID(0)
    , m_currentComponentTypeID(0)
    {
        std::memset(m_containers, 0, sizeof(Container*) * MAX_CONTAINERS);
        std::memset(m_componentIDs, 0, sizeof(ComponentID) * MAX_INTERFACES * MAX_CONTAINERS);
        std::memset(m_subscriptions, 0, sizeof(bool) * MAX_INTERFACES*MAX_MESSAGE_TYPES);
    }

    ComponentManager::~ComponentManager() {
    }

    const ComponentID& ComponentManager::createComponent(const ComponentTypeID& type) {
        unsigned int typeIndex = type; //conversion to index
        tComponentCreator creator = m_componentInfos[typeIndex].Creator;
        unsigned int componentIndex = m_componentIndices.allocate();
        ComponentID cid(componentIndex); // convert to ComponentID
        ComponentBase* component = (*creator)(cid);
        m_instanceInfos[componentIndex].Component = type;
        m_instanceInfos[componentIndex].Pointer = component;
        return component->getComponentID();
    }

    void ComponentManager::destroyComponent(const ComponentID& cid) {
        unsigned int index = cid.getIndex(); //conversion to index
        ComponentTypeID ctid = m_instanceInfos[index].Component;
        ComponentBase* cmp = m_instanceInfos[index].Pointer;
        m_instanceInfos[index].Pointer = 0;
        unsigned int typeIndex = ctid; //conversion to index
        tComponentDestroyer destroyer = m_componentInfos[typeIndex].Destoyer;
        (*destroyer)(cmp);
    }

    ComponentBase* ComponentManager::getComponent(const ComponentID& cid) {
        return m_instanceInfos[cid.getIndex()].Pointer;
    }

    ComponentManager& ComponentManager::getInstance() {
        if (!m_instancePtr)
            m_instancePtr = new ComponentManager;
        return *m_instancePtr;
    }
    
    ObjectID ComponentManager::registerContainer(Container* container) {
        unsigned int index = m_containerIndices.allocate();
        ObjectID oid(index);
        m_containers[index] = container;
        std::memset(&m_componentIDs[index * MAX_INTERFACES], 0, sizeof(ComponentID) * MAX_INTERFACES);
        std::cout << "Object " << oid.getIndex() << " registered." << std::endl;
        return oid;
    }
    
    InterfaceTypeID ComponentManager::registerInterface(int subscription) {
        InterfaceTypeID iid = getNewInterfaceTypeID();
        unsigned int iid_index = iid;
        for(int m = 0; m < MAX_MESSAGE_TYPES; m++)
            if(subscription&((int)std::pow((float)2,m))) {
                std::cout << "Registering interface " << iid_index << " for MID " << m << std::endl;
                m_subscriptions[iid_index + MAX_INTERFACES * m] = true;
            }
        return iid;
    }

    void ComponentManager::deregisterContainer(const ObjectID& oid) {
        unsigned int index = oid.getIndex();
        m_containers[index] = 0;
        std::memset(&m_componentIDs[index * MAX_INTERFACES], 0, sizeof(ComponentID) * MAX_INTERFACES);
        m_containerIndices.free(index);
        std::cout << "Object " << oid.getIndex() << " deregistered." << std::endl;
    }
    
    Container* ComponentManager::getContainer(const ObjectID& oid) {
        unsigned int index = oid.getIndex();
        return m_containers[index];
    }

    InterfaceTypeID ComponentManager::getNewInterfaceTypeID() {
        std::cout << "Interface " << m_currentInterfaceTypeID << " registered." << std::endl;
        return m_currentInterfaceTypeID++;
    }

    ComponentTypeID ComponentManager::registerComponentType(const InterfaceTypeID& iid, tComponentCreator c, tComponentDestroyer d) {
        m_componentInfos[m_currentComponentTypeID].Interface = iid;
        m_componentInfos[m_currentComponentTypeID].Creator = c;
        m_componentInfos[m_currentComponentTypeID].Destoyer = d;
        std::cout << "Component " << m_currentComponentTypeID << " registered." << std::endl;
        std::cout << " - Interface " << iid << std::endl;
        return m_currentComponentTypeID++;
    }
    
    void ComponentManager::broadcastMessage(MessageBase& msg) {
        unsigned int mid_index = msg.m_MID;
        for(int i = 0; i < MAX_INTERFACES; i++)
            if(m_subscriptions[i + MAX_INTERFACES * mid_index]) {
               InterfaceTypeID iid = i;
               broadcastMessage(iid, msg);
            }

    }

    void ComponentManager::broadcastMessage(const InterfaceTypeID& iid, MessageBase& msg) {
        msg.Addressee = ObjectID();
        msg.Sender = ObjectID();
        for(int o = 0; o < MAX_CONTAINERS; o++) {
            ObjectID oid(o);
            const ComponentID& cid = getComponentID(iid, oid);
            if(cid.isValid()) {
                ComponentBase* c = getComponent(cid);
                if(c)
                    c->handleMessage(msg);
            }
        }
    }
    
    MessageResult ComponentManager::sendMessage(const InterfaceTypeID& iid, const ObjectID& oid, MessageBase& msg ) {
        const ComponentID& cid = getComponentID(iid, oid);
            if(cid.isValid()) {
                ComponentBase* component = getComponent(cid);
                if(component) {
                    // write on envelope
                    // this changes msg!
                    msg.Addressee = oid;
                    msg.Sender = ObjectID();
                    return component->handleMessage(msg);
                }
                std::cerr << "Component invalid in container " << oid.getIndex() << std::endl;
                return MR_ERROR; // failed to deliver
            }
            std::cerr << "Failed to find an implementation of interface " << iid
                        << " in Container " << oid.getIndex() << std::endl;
            return MR_ERROR; // failed to deliver
    }



}

