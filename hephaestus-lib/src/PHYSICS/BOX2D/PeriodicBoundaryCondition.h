/* 
 * File:   PeriodicBoundaryCondition.h
 * Author: chris
 *
 * Created on June 3, 2014, 3:44 PM
 */

#ifndef PERIODICBOUNDARYCONDITION_H
#define	PERIODICBOUNDARYCONDITION_H

#include "../BoundaryCondition.h"
#include "../../MATH/vec234.h"
#include <Box2D/Common/b2Math.h>

namespace PHYSICS {
    namespace BOX2D {

        class PeriodicBoundaryCondition : public PHYSICS::BoundaryCondition {
        public:
            PeriodicBoundaryCondition();
            virtual ~PeriodicBoundaryCondition();
            virtual void apply(PHYSICS::System& system);
            virtual void onResize(float width, float height);
        private:
            b2Vec2 clampCoordinates(const b2Vec2& position);

            MATH::vec2 m_worldDimensions;
            MATH::vec2 m_padding;
        };
    }
}
#endif	/* PERIODICBOUNDARYCONDITION_H */

