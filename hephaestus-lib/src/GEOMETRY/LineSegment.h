/* 
 * File:   LineSegment.h
 * Author: chris
 *
 * Created on June 17, 2014, 10:06 AM
 */

#ifndef LINESEGMENT_H
#define	LINESEGMENT_H

#include "../MATH/vec234.h"
#include <utility> 

namespace GEOMETRY {

    namespace LineSegment_CONST {
        const float EPS = 10e-6;
    }
    
    class LineSegment {
    public:
        LineSegment();
        LineSegment(const MATH::vec2& start, const MATH::vec2& end);
        bool isPointOnSegment(const MATH::vec2& point) const;
        float distSquared(const MATH::vec2& p) const;
        std::pair<LineSegment, LineSegment> split(const MATH::vec2& p) const;
        virtual ~LineSegment();
        const MATH::vec2& getStart() const { return m_start; }
        const MATH::vec2& getEnd() const { return m_end; }
    private:
        inline float sqr(float x) const { return x * x; }
        inline float dist2(const MATH::vec2& v, const MATH::vec2&  w) const { return sqr(v.x - w.x) + sqr(v.y - w.y); }
        MATH::vec2 m_start;
        MATH::vec2 m_end;
    };
}
#endif	/* LINESEGMENT_H */

