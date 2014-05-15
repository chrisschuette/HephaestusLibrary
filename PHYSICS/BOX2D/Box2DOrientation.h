/* 
 * File:   Box2DOrientation.h
 * Author: chris
 *
 * Created on June 21, 2013, 5:35 PM
 */

#ifndef BOX2DORIENTATION_H
#define	BOX2DORIENTATION_H

#include "../Orientation.h"

namespace PHYSICS {
    namespace BOX2D {
class Box2DOrientation: public PHYSICS::Orientation {
public:
    Box2DOrientation();
    Box2DOrientation(float angle);
    virtual ~Box2DOrientation();
    operator float() const { return m_angle; }
private:
    float m_angle;
};
    }
}
#endif	/* BOX2DORIENTATION_H */

