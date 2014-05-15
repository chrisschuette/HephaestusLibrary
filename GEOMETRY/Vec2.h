/* 
 * File:   Vec2.h
 * Author: chris
 *
 * Created on February 3, 2014, 10:49 PM
 */

#ifndef VEC2_H
#define	VEC2_H

namespace GEOMETRY {

    template <class Scalar>
    class Vec2 {
    public:
        Vec2() {} 
        Vec2(Scalar x, Scalar y) : x(x), y(y) {} 
        Scalar x;
        Scalar y;
    };
}

#endif	/* VEC2_H */

