/* 
 * File:   Polygon.h
 * Author: chris
 *
 * Created on May 30, 2014, 1:20 AM
 */

#ifndef POLYGON_H
#define	POLYGON_H

#include "../MATH/vec234.h"
#include "Triangle.h"

#include <vector>
#include <string>

namespace GEOMETRY {
    class Polygon {
    public:
        Polygon();
        virtual ~Polygon();
        
        void addVertex(const MATH::vec2& vertex);
        void removeVertex(int i);
        virtual Polygon* clone() const;
        
        float calculateArea() const;
        std::vector<Triangle> triangulate() const;
        
        void scale(float factor);
        MATH::vec2 calculateCenterOfMass() const;
        void translate(const MATH::vec2& dr);
        
        int countSharedVertices(const Polygon& polygon);
        
        std::string toString();
        const std::vector<MATH::vec2>& getVertices() const { return m_vertices; }
    private:
        bool snip(int u,int v,int w,int n,int *V) const;
        std::vector<MATH::vec2> m_vertices;
    };
}

namespace LOG {
    const LOG::Core& operator<<(const LOG::Core&, const GEOMETRY::Polygon&);
}
#endif	/* POLYGON_H */

