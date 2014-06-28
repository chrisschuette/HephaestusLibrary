/* 
 * File:   Body.cpp
 * Author: chris
 * 
 * Created on May 21, 2014, 7:41 PM
 */

#include "Body.h"
#include "BodyUserData.h"

namespace PHYSICS {
    Body::Body(System& world)
    : m_world(world)
    , m_userData(0)
    {
    }

    Body::~Body() {
        if(m_userData)
            delete m_userData;
    }
}
