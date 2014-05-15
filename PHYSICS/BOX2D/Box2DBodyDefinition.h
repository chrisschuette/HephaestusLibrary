/* 
 * File:   Box2DBodyDefinition.h
 * Author: chris
 *
 * Created on June 19, 2013, 2:06 AM
 */

#ifndef BOX2DBODYDEFINITION_H
#define	BOX2DBODYDEFINITION_H

#include "../BodyDefinition.h"
#include <Box2D/Dynamics/b2Body.h>

namespace PHYSICS {
    namespace BOX2D {
        class Box2DSystem;

        class Box2DBodyDefinition : public PHYSICS::BodyDefinition {
        public:
            Box2DBodyDefinition();
            virtual ~Box2DBodyDefinition();

            virtual void setOrientation(const Orientation& orientation);
            virtual void setPosition(const Position& position);
            virtual void setBodyType(BODY_TYPE type);

        private:
            b2BodyDef m_def;
            friend class Box2DSystem;
        };
    }
}
#endif	/* BOX2DBODYDEFINITION_H */

