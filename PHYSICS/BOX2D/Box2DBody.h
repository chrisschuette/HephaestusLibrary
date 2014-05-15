/* 
 * File:   Box2DBody.h
 * Author: chris
 *
 * Created on June 19, 2013, 2:03 AM
 */

#ifndef BOX2DBODY_H
#define	BOX2DBODY_H

#include "../Body.h"
#include <Box2D/Dynamics/b2Body.h>

namespace PHYSICS {
    namespace BOX2D {
        class Box2DBodyDefinition;
        class Box2DSystem;
        class Box2DBodyPart;
class Box2DBody: public PHYSICS::Body {
public:
    virtual int getBodyType() const;
    b2Body* getBodyPtr() { return m_body; }
protected:
    Box2DBody(tID ID, b2Body* body/*, const Box2DBodyDefinition& definition*/, Box2DSystem& system);
    virtual ~Box2DBody();
    void attachBodyPart(const Box2DBodyPart& bodyPart);
    b2Body* m_body;
    friend class Box2DSystem;
};
    }
}
#endif	/* BOX2DBODY_H */

