/* 
 * File:   Vector2D.h
 * Author: chris
 *
 * Created on June 21, 2013, 5:08 PM
 */

#ifndef VECTOR2D_H
#define	VECTOR2D_H

#include <utility>

namespace MATH {
    template <class T>
class Vec2 {
public:
    Vector2D();
    Vector2D(T x, T y);
    virtual ~Vector2D();
    inline T& x() const { return m_x; }
    inline T& y() const { return m_x; }
private:
    T m_x;
    T m_y;
};
}
#endif	/* VECTOR2D_H */

