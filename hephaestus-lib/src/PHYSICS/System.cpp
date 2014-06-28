/* 
 * File:   System.cpp
 * Author: chris
 * 
 * Created on May 21, 2014, 7:20 PM
 */

#include "System.h"

#include "CollisionListener.h"
#include "BoundaryCondition.h"

namespace PHYSICS {

    System::System(float scalingFactor)
    : m_scalingFactor(scalingFactor)
    , m_collisionListener(0)
    , m_boundaryCondition(0) {
    }

    System::~System() {
        if (m_boundaryCondition)
            delete m_boundaryCondition;
        if (m_collisionListener)
            delete m_collisionListener;
    }

    void System::update() {
        if(m_boundaryCondition)
            m_boundaryCondition->apply(*this);
    }

    void System::onResize(float width, float height) {
        if(m_boundaryCondition)
            m_boundaryCondition->onResize(width, height);
    }


}
