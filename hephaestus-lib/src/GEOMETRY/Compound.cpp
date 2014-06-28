/* 
 * File:   Compound.cpp
 * Author: chris
 * 
 * Created on May 30, 2014, 1:24 AM
 */

#include "Compound.h"
#include "Polygon.h"

#include <algorithm>
#include <iostream>
#include <cmath>

namespace GEOMETRY {

    struct PolygonDuplicator {

        PolygonDuplicator(std::list<Polygon*>& target) : m_target(target) {
        }

        inline void operator()(Polygon * p) {
            m_target.push_back(p->clone());
        }
    private:
        std::list<Polygon*>& m_target;
    };

    struct PolygonDeleter {

        inline void operator()(Polygon * p) {
            delete p;
        }
    };
    
    struct PolygonTranslator {

        PolygonTranslator(const MATH::vec2& r) : dr(r) {}
        const MATH::vec2& dr;
        inline void operator()(Polygon * p) {
            p->translate(dr);
        }
    };

    struct CenterOfMassCalculator {

        CenterOfMassCalculator(MATH::vec2& c) : com(c) {
            m_com.x = 0;
            m_com.y = 0;
            M = 0;
        }

        inline void operator()(Polygon * p) {
            float m = fabs(p->calculateArea());
            M += m;
            MATH::vec2 r = p->calculateCenterOfMass();
            m_com.x += m * r.x;
            m_com.y += m * r.y;
            
            // update com
            com.x = m_com.x / M;
            com.y = m_com.y / M;
        }
    private:
        float M;
        MATH::vec2 m_com;
        MATH::vec2& com;
    };

    Compound::Compound() {
    }

    Compound::Compound(const Compound& orig) {
        std::for_each(orig.m_shapes.begin(), orig.m_shapes.end(), PolygonDuplicator(m_shapes));
    }

    Compound& Compound::operator=(const Compound& orig) {
        if (this == &orig)
            return *this;

        // abbauen
        std::for_each(m_shapes.begin(), m_shapes.end(), PolygonDeleter());
        m_shapes.clear();
        std::for_each(orig.m_shapes.begin(), orig.m_shapes.end(), PolygonDuplicator(m_shapes));
        return *this;
    }

    Compound::~Compound() {
        std::for_each(m_shapes.begin(), m_shapes.end(), PolygonDeleter());
    }

    void Compound::addPolygon(Polygon* p) {
        m_shapes.push_back(p);
    }

    void Compound::removePolygon(Polygon* p) {
        m_shapes.remove(p);
    }

    MATH::vec2 Compound::calculateCenterOfMass() const {
        MATH::vec2 com;
        std::for_each(m_shapes.begin(), m_shapes.end(), CenterOfMassCalculator(com));
        return com;
    }
    
     void Compound::translate(const MATH::vec2& dr) {
         std::for_each(m_shapes.begin(), m_shapes.end(), PolygonTranslator(dr));
     }
}
