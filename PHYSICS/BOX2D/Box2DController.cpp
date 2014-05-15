/* 
 * File:   Box2DController.cpp
 * Author: chris
 * 
 * Created on June 22, 2013, 11:17 AM
 */

#include "Box2DController.h"
#include "Box2DSystem.h"

namespace PHYSICS {
    namespace BOX2D {
Box2DController::Box2DController()
: Controller()
, m_timeStep(1.0f / 60.0f)
, m_vIterations(6)
, m_pIterations(2)
{

}

Box2DController::~Box2DController() {
}

void Box2DController::evolve(System& system) {
    Box2DSystem& mySystem = static_cast<Box2DSystem&>(system);
    mySystem.getWorldPtr()->Step(m_timeStep, m_vIterations, m_pIterations);
}

    }
}
