/* 
 * File:   Compound.h
 * Author: chris
 *
 * Created on May 30, 2014, 1:24 AM
 */

#ifndef COMPOUND_H
#define	COMPOUND_H

#include "../MATH/vec234.h"
#include <list>

namespace GEOMETRY {
    class Polygon;
    class Compound {
    public:
        Compound();
        Compound(const Compound& orig);
        Compound& operator=(const Compound& orig);
        virtual ~Compound();
        
        void addPolygon(Polygon* p);
        void removePolygon(Polygon* p);
        int countPolygons() const { return m_shapes.size(); }
        
        MATH::vec2 calculateCenterOfMass() const;
        
        void translate(const MATH::vec2& dr);
        
        const std::list<Polygon*>& getShapes() const { return m_shapes; }
        std::list<Polygon*>& getShapes() { return m_shapes; }
    private:
        std::list<Polygon*> m_shapes;
    };
}
#endif	/* COMPOUND_H */

