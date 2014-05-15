/* 
 * File:   Box2DBodyPart.h
 * Author: chris
 *
 * Created on June 22, 2013, 1:43 AM
 */

#ifndef BOX2DBODYPART_H
#define	BOX2DBODYPART_H

#include "../BodyPart.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

namespace PHYSICS {
    namespace BOX2D {
        
class Box2DBodyPart: public PHYSICS::BodyPart {
public:
    Box2DBodyPart();
    virtual ~Box2DBodyPart();
    void setDimensions(float width, float height);
    const b2FixtureDef* getPartDefinition() const { return &m_def; }
private:
    b2FixtureDef m_def;
    b2PolygonShape m_shape;
};
    }
}
#endif	/* BOX2DBODYPART_H */

