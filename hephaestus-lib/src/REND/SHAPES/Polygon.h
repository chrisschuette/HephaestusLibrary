/* 
 * File:   Polygon.h
 * Author: chris
 *
 * Created on May 30, 2014, 1:31 AM
 */

#ifndef RENDSHAPESPOLYGON_H
#define	RENDSHAPESPOLYGON_H

#include "../../GEOMETRY/Polygon.h"

namespace REND {
    namespace SHAPES {

        class Polygon: public GEOMETRY::Polygon {
        public:
            Polygon();
            virtual ~Polygon();
            
            void setStrokeColor(const MATH::vec4& strokeColor) { m_strokeColor = strokeColor; }
            void setFillColor(const MATH::vec4& fillColor) { m_fillColor = fillColor; }
            const MATH::vec4& getFillColor() const { return m_fillColor; }
            virtual Polygon* clone() const { return new Polygon(*this); }
        private:
            MATH::vec4 m_strokeColor;
            MATH::vec4 m_fillColor;
        };
    }
}
#endif	/* RENDSHAPESPOLYGON_H */

