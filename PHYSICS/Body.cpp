/* 
 * File:   Body.cpp
 * Author: chris
 * 
 * Created on June 19, 2013, 1:45 AM
 */

#include "Body.h"
#include "System.h"
#include "../ERR/ERR.h"

namespace PHYSICS {

    Body::Body(tID ID/*, const BodyDefinition& definition*/, System& system)
    : SYS::IsReferenceCounted< Body >(system.getReferencePool())
    , m_ID(ID)
    , m_system(system)
    //, m_definition(definition)
    {
    }

    Body::Body(const Body& orig)
    : SYS::IsReferenceCounted< Body >(orig.m_system.getReferencePool())
    , m_ID(orig.m_ID)
    , m_system(orig.m_system) {
        THROWS("Body not copyable");
    }

    Body::~Body() {
    }
}
