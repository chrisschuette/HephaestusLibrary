/* 
 * File:   Rectangle.h
 * Author: chris
 *
 * Created on February 2, 2014, 6:46 PM
 */

#ifndef RECTANGLE_H
#define	RECTANGLE_H

#include "Vec2.h"

namespace GEOMETRY {
    template <class Scalar>
    class Rectangle {
    public:
        Rectangle() { }
        Scalar getWidth() const { return m_dimension.x; }
        Scalar getHeight() const { return m_dimension.y; } 
        
        void setPosition(Vec2<Scalar> position) { m_position = position; }
        void setDimenions(Vec2<Scalar> dimension) { m_dimension = dimension; }
        
        void setDimensions(Scalar w, Scalar h) {
            m_dimension.x = w;
            m_dimension.y = h;
        }
        
        const Vec2<Scalar>& getDimensions() const { return m_dimension; }
        const Vec2<Scalar>& getPosition() const { return m_position; }
    protected:
        Vec2<Scalar> m_position;
        Vec2<Scalar> m_dimension;
    };
}
#endif	/* RECTANGLE_H */

