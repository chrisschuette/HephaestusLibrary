/* 
 * File:   PeriodicBoundaryCondition.cpp
 * Author: chris
 * 
 * Created on June 3, 2014, 3:44 PM
 */

#include "PeriodicBoundaryCondition.h"
#include "System.h"
#include "../../LOG/Core.h"
#include <Box2D/Dynamics/b2Body.h>

#define NAME "PeriodicBoundaryCondition"

namespace PHYSICS {
    namespace BOX2D {

        PeriodicBoundaryCondition::PeriodicBoundaryCondition() : PHYSICS::BoundaryCondition() {
            m_worldDimensions.x = -1;
            m_worldDimensions.y = -1;
            m_padding.x = 5;
            m_padding.y = 5;
        }

        PeriodicBoundaryCondition::~PeriodicBoundaryCondition() {
        }

        void PeriodicBoundaryCondition::apply(PHYSICS::System& system) {
            if ((m_worldDimensions.x > 0) && (m_worldDimensions.y > 0)) {
                PHYSICS::BOX2D::System& s = static_cast<PHYSICS::BOX2D::System&> (system);
                b2World& world = s.getBox2DWorld();
                for (b2Body* b = world.GetBodyList(); b; b = b->GetNext())
                    b->SetTransform(clampCoordinates(b->GetPosition()), b->GetAngle());
            }
        }

        void PeriodicBoundaryCondition::onResize(float width, float height) {
            m_worldDimensions.x = width;
            m_worldDimensions.y = height;
            L(normal) << "onResize: " << m_worldDimensions.x << " " << m_worldDimensions.y;
        }

        b2Vec2 PeriodicBoundaryCondition::clampCoordinates(const b2Vec2& position) {
            b2Vec2 new_position = position;
            assert((m_worldDimensions.x > 0) && (m_worldDimensions.y > 0));

            while (new_position.x < -m_padding.x)
                new_position.x += m_worldDimensions.x + 2 * m_padding.x;
            while (new_position.x > m_worldDimensions.x + m_padding.x)
                new_position.x -= m_worldDimensions.x + 2 * m_padding.x;

            while (new_position.y < -m_padding.y)
                new_position.y += m_worldDimensions.y + 2 * m_padding.y;
            while (new_position.y > m_worldDimensions.y + m_padding.y)
                new_position.y -= m_worldDimensions.y + 2 * m_padding.y;
            return new_position;
        }
    }
}