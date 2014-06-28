/* 
 * File:   Triangle.cpp
 * Author: chris
 * 
 * Created on May 30, 2014, 3:17 PM
 */

#include "Triangle.h"

namespace GEOMETRY {

    Triangle::Triangle(const MATH::vec2& A,
            const MATH::vec2& B,
            const MATH::vec2& C) {
        m_vertices[0] = A;
        m_vertices[1] = B;
        m_vertices[2] = C;

    }

    Triangle::~Triangle() {
    }

    bool Triangle::isPointInside(const MATH::vec2& P) {
        float ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;
        float cCROSSap, bCROSScp, aCROSSbp;
        ax = m_vertices[2].x - m_vertices[1].x;
        ay = m_vertices[2].y - m_vertices[1].y;
        bx = m_vertices[0].x - m_vertices[2].x;
        by = m_vertices[0].y - m_vertices[2].y;
        cx = m_vertices[1].x - m_vertices[0].x;
        cy = m_vertices[1].y - m_vertices[0].y;
        apx = P.x - m_vertices[0].x;
        apy = P.y - m_vertices[0].y;
        bpx = P.x - m_vertices[1].x;
        bpy = P.y - m_vertices[1].y;
        cpx = P.x - m_vertices[2].x;
        cpy = P.y - m_vertices[2].y;
        aCROSSbp = ax * bpy - ay*bpx;
        cCROSSap = cx * apy - cy*apx;
        bCROSScp = bx * cpy - by*cpx;
        return ((aCROSSbp >= 0.0f) && (bCROSScp >= 0.0f) && (cCROSSap >= 0.0f));
    }

}

namespace LOG {

    const LOG::Core& operator<<(const LOG::Core& core, const GEOMETRY::Triangle& triangle) {
        core << triangle.getA().x << ";" << triangle.getA().y << " "
                << triangle.getB().x << ";" << triangle.getB().y << " "
                << triangle.getC().x << ";" << triangle.getC().y;
        return core;
    }
}