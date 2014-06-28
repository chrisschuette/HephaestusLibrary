/* 
 * File:   Resource.cpp
 * Author: chris
 * 
 * Created on June 9, 2013, 8:36 PM
 */

#include "Resource.h"
#include "Loader.h"

namespace FSVR {

    Resource::Resource()
    : m_state(INACTIVE)
    , m_instantiation(IMMEDIATELY)
    , m_loader(0)
    , m_eventListener(0) {
    }
    
    Resource::Resource(tRID id)
    : m_ID(id)
    , m_state(INACTIVE)
    , m_instantiation(IMMEDIATELY)
    , m_loader(0)
    , m_eventListener(0) {
    }

    Resource::~Resource() {
        if (m_loader)
            delete m_loader;
        m_loader = 0;
    }

    Resource::STATE Resource::getState() const {
        return m_state;
    }

    void Resource::setState(Resource::STATE newState) {
        m_state = newState;
    }
    
    bool Resource::isLoaderToBeDeleted() {
        if(m_instantiation == IMMEDIATELY)
            return true;
        else 
            return false;
    }

}


