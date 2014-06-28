/* 
 * File:   Polygon.cpp
 * Author: chris
 * 
 * Created on May 30, 2014, 1:20 AM
 */

#include "Polygon.h"
#include "../UTIL/string.h"
#include <assert.h>

namespace GEOMETRY {

    Polygon::Polygon() {
    }

    Polygon::~Polygon() {
    }

    void Polygon::addVertex(const MATH::vec2& vertex) {
        m_vertices.push_back(vertex);
    }

    void Polygon::removeVertex(int i) {
        assert(i >= 0);
        assert(i < m_vertices.size());
        m_vertices.erase(m_vertices.begin() + i);
    }

    Polygon* Polygon::clone() const {
        return new Polygon(*this);
    }

    float Polygon::calculateArea() const {
        int n = m_vertices.size();
        float A = 0.f;
        for (int p = n - 1, q = 0; q < n; p = q++)
            A += m_vertices[p].x * m_vertices[q].y - m_vertices[q].x * m_vertices[p].y;
        return 0.5f * A;
    }

    bool Polygon::snip(int u, int v, int w, int n, int *V) const {
        MATH::vec2 P;
        Triangle t(m_vertices[V[u]], m_vertices[V[v]], m_vertices[V[w]]);
        if (0.0000000001f > (((t.getB().x - t.getA().x)*(t.getC().y - t.getA().y)) - ((t.getB().y - t.getA().y)*(t.getC().x - t.getA().x)))) return false;
        for (int p = 0; p < n; p++) {
            if ((p == u) || (p == v) || (p == w)) continue;
            P.x = m_vertices[V[p]].x;
            P.y = m_vertices[V[p]].y;
            if (t.isPointInside(P)) return false;
        }
        return true;
    }

    void Polygon::scale(float factor) {
        for (std::vector<MATH::vec2>::iterator i = m_vertices.begin(), e = m_vertices.end();
                i != e; ++i) {
            (*i).x *= factor;
            (*i).y *= factor;
        }
    }

    MATH::vec2 Polygon::calculateCenterOfMass() const {
        MATH::vec2 com;
        com.x = 0;
        com.y = 0;
        int n = m_vertices.size();
        float A = calculateArea();
        for (int p = n - 1, q = 0; q < n; p = q++) {
            com.x += (m_vertices[p].x + m_vertices[q].x) * (m_vertices[p].x * m_vertices[q].y - m_vertices[q].x * m_vertices[p].y) / (6.f * A);
            com.y += (m_vertices[p].y + m_vertices[q].y) * (m_vertices[p].x * m_vertices[q].y - m_vertices[q].x * m_vertices[p].y) / (6.f * A);
        }

        return com;
    }

    void Polygon::translate(const MATH::vec2& dr) {
        for (std::vector<MATH::vec2>::iterator i = m_vertices.begin(), e = m_vertices.end(); i != e; ++i) {
            (*i).x += dr.x;
            (*i).y += dr.y;
        }
    }

    int Polygon::countSharedVertices(const Polygon& polygon) {
        int count = 0;
        for (std::vector<MATH::vec2>::const_iterator i = m_vertices.begin(), e = m_vertices.end(); i != e; ++i)
            for (std::vector<MATH::vec2>::const_iterator j = polygon.m_vertices.begin(), f = polygon.m_vertices.end(); j != f; ++j)
                if ((std::pow((*i).x - (*j).x, 2) + std::pow((*i).y - (*j).y, 2)) < 1e-4)
                    count++;

        return count;
    }

    std::string Polygon::toString() {
        std::string points;
        for (int i = 0; i < m_vertices.size(); i++)
            points += UTIL::toString(m_vertices[i].x) + ":" + UTIL::toString(m_vertices[i].y) + " ";
        return points;
    }

    std::vector<Triangle> Polygon::triangulate() const {
        std::vector<Triangle> triangulation;

        /* allocate and initialize list of Vertices in polygon */

        int n = m_vertices.size();
        if (n < 3) return triangulation;

        int *V = new int[n];

        /* we want a counter-clockwise polygon in V */

        if (0.0f < calculateArea())
            for (int v = 0; v < n; v++) V[v] = v;
        else
            for (int v = 0; v < n; v++) V[v] = (n - 1) - v;

        int nv = n;

        /*  remove nv-2 Vertices, creating 1 triangle every time */
        int count = 2 * nv; /* error detection */


        for (int m = 0, v = nv - 1; nv > 2;) {
            /* if we loop, it is probably a non-simple polygon */
            if (0 >= (count--)) {
                //** Triangulate: ERROR - probable bad polygon!
                return std::vector<Triangle>();
            }

            /* three consecutive vertices in current polygon, <u,v,w> */
            int u = v;
            if (nv <= u) u = 0; /* previous */
            v = u + 1;
            if (nv <= v) v = 0; /* new v    */
            int w = v + 1;
            if (nv <= w) w = 0; /* next     */

            if (snip(u, v, w, nv, V)) {
                int a, b, c, s, t;

                /* true names of the vertices */
                a = V[u];
                b = V[v];
                c = V[w];

                /* output Triangle */
                Triangle triangle(m_vertices[a], m_vertices[b], m_vertices[c]);
                triangulation.push_back(triangle);

                m++;

                /* remove v from remaining polygon */
                for (s = v, t = v + 1; t < nv; s++, t++) V[s] = V[t];
                nv--;

                /* resest error detection counter */
                count = 2 * nv;
            }
        }

        delete [] V;

        return triangulation;

    }


}

namespace LOG {

    const LOG::Core& operator<<(const LOG::Core& core, const GEOMETRY::Polygon& polygon) {
        core << "Polygon: ";
        const std::vector<MATH::vec2>& vertices = polygon.getVertices();
        for( int i = 0; i < vertices.size(); i++ )
            core << vertices[i].x << " " << vertices[i].y << " // ";
        return core;
    }
}