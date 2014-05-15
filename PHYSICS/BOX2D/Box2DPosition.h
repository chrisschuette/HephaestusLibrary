/* 
 * File:   Box2DPosition.h
 * Author: chris
 *
 * Created on June 21, 2013, 5:31 PM
 */

#ifndef BOX2DPOSITION_H
#define	BOX2DPOSITION_H

#include "../Position.h"
#include <Box2D/Common/b2Math.h>

namespace PHYSICS {
    namespace BOX2D {
    class Box2DPosition: public PHYSICS::Position {
public:
    Box2DPosition();
    Box2DPosition(float x, float y);
    virtual ~Box2DPosition();
    void set(float x, float y);
    operator b2Vec2() { return m_position; }
    operator const b2Vec2() const { return m_position; }
private:
    b2Vec2 m_position;
};
}
}
#endif	/* BOX2DPOSITION_H */

