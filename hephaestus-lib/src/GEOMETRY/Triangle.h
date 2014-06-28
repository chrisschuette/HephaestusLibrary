/* 
 * File:   Triangle.h
 * Author: chris
 *
 * Created on May 30, 2014, 3:17 PM
 */

#ifndef TRIANGLE_H
#define	TRIANGLE_H

#include "../MATH/vec234.h"
#include "../LOG/AutoTerminator.h"
#include "../LOG/Core.h"

namespace GEOMETRY {

    class Triangle {
    public:
        Triangle(const MATH::vec2& A,
                const MATH::vec2& B,
                const MATH::vec2& C);
        virtual ~Triangle();

        inline const MATH::vec2& getA() const {
            return m_vertices[0];
        }

        inline const MATH::vec2& getB() const {
            return m_vertices[1];
        }

        inline const MATH::vec2& getC() const {
            return m_vertices[2];
        }

        bool isPointInside(const MATH::vec2& P);
    private:
        MATH::vec2 m_vertices[3];
    };

    //R operator <<(K a, S b);
}

namespace LOG {
    const LOG::Core& operator<<(const LOG::Core&, const GEOMETRY::Triangle&);
}
#endif	/* TRIANGLE_H */

