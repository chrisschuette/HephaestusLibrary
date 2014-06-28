/* 
 * File:   LineSegment.cpp
 * Author: chris
 * 
 * Created on June 17, 2014, 10:06 AM
 */

#include "LineSegment.h"
#include "../ERR/ERR.h"
#include <cmath>

namespace GEOMETRY {

    LineSegment::LineSegment() {
    }

    LineSegment::LineSegment(const MATH::vec2& start, const MATH::vec2& end)
    : m_start(start)
    , m_end(end) {

    }

    LineSegment::~LineSegment() {
    }
    
    std::pair<LineSegment, LineSegment> LineSegment::split(const MATH::vec2& p) const {
        if(!isPointOnSegment(p))
            THROWS("Point p is not on line");
        return std::pair<LineSegment, LineSegment>(LineSegment(m_start,p),LineSegment(p,m_end));
    }

    float LineSegment::distSquared(const MATH::vec2& p) const {
        float l2 = dist2(m_start, m_end);
        if (std::fabs(l2) < LineSegment_CONST::EPS) return dist2(p, m_start);
        float t = ((p.x - m_start.x) * (m_end.x - m_start.x) + (p.y - m_start.y) * (m_end.y - m_start.y)) / l2;
        if (t < 0) return dist2(p, m_start);
        if (t > 1) return dist2(p, m_end);
        MATH::vec2 x;
        x.x = m_start.x + t * (m_end.x - m_start.x);
        x.y = m_start.y + t * (m_end.y - m_start.y);
        return dist2(p,x);
    }

    bool LineSegment::isPointOnSegment(const MATH::vec2& p) const {
        if(std::fabs(distSquared(p)) < LineSegment_CONST::EPS)
            return true;
        return false;
    }
}
