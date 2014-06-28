/* 
 * File:   BodyPartDescription.cpp
 * Author: chris
 * 
 * Created on May 21, 2014, 11:37 PM
 */

#include "BodyPartDescription.h"

namespace PHYSICS {
    namespace BOX2D {

        BodyPartDescription::BodyPartDescription() : PHYSICS::BodyPartDescription() {
            m_description.shape = &m_shape;
            m_description.density = 1;
        }

        BodyPartDescription::~BodyPartDescription() {
        }

        void BodyPartDescription::setDimensions(float halfWidth, float halfHeight) {
            m_shape.SetAsBox(halfWidth, halfHeight);
        }

        void BodyPartDescription::setSensor(bool sensor) {
            m_description.isSensor = sensor;
        }

        void BodyPartDescription::setPolygonShape(const std::list<MATH::vec2>& outline) {
            b2Vec2 points[outline.size()];
            int c = 0;
            for (std::list<MATH::vec2>::const_iterator i = outline.begin(), e = outline.end(); i != e; ++i) {
                points[c].x = (*i).x;
                points[c].y = (*i).y;
                c++;
            }
            m_shape.Set(points, outline.size());
        }
        
        BodyPartDescription* BodyPartDescription::clone() const {
            return new BodyPartDescription(*this);
        }

    }
}

