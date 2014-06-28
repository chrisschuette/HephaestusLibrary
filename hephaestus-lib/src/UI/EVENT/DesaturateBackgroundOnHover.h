/* 
 * File:   DesaturateBackgroundOnHover.h
 * Author: chris
 *
 * Created on May 28, 2014, 11:16 AM
 */

#ifndef DESATURATEBACKGROUNDONHOVER_H
#define	DESATURATEBACKGROUNDONHOVER_H

#include "EventHandler.h"
#include "MouseEvent.h"
#include "../../MATH/vec234.h"
#include "../../LOG/Core.h"

#include <cmath>

#define NAME "DesaturateBackgroundOnHover"

namespace UI {
    namespace EVENT {

        template <class T>
        class DesaturateBackgroundOnHover : public EventHandler {
        public:

            DesaturateBackgroundOnHover(EventResponder& responder) : EventHandler(responder) {
                m_previousColor = static_cast<T&> (m_responder).getBackgroundColor();
                m_desaturated = false;
                //desaturate(m_mouseInColor,m_mouseOutColor);
                //static_cast<T&>(m_responder).setBackgroundColor(m_mouseOutColor);
            }

            virtual EVENT::Event::RESULT handleEvent(const Event& e) {
                const MouseEvent& mouseEvent = static_cast<const MouseEvent&> (e);
                if (mouseEvent.getType() == MouseEvent::MOUSEIN) {
                    if (!m_desaturated) {
                        m_previousColor = static_cast<T&> (m_responder).getBackgroundColor();
                        MATH::vec4 newColor;
                        newColor.r = std::min(1.0, 0.5 + m_previousColor.r);
                        newColor.g = std::min(1.0, 0.5 + m_previousColor.g);
                        newColor.b = std::min(1.0, 0.5 + m_previousColor.b);
                        newColor.a = m_previousColor.a;
                        static_cast<T&> (m_responder).setBackgroundColor(newColor);
                        m_desaturated = true;
                    }
                    return EVENT::Event::ACCEPTED;
                } else if (mouseEvent.getType() == MouseEvent::MOUSEOUT) {
                    if (m_desaturated) {
                        static_cast<T&>(m_responder).setBackgroundColor(m_previousColor);
                        m_desaturated = false;
                    }
                    return EVENT::Event::ACCEPTED;
                }
                return Event::REJECTED;
            }

            void desaturate(const MATH::vec4& c, MATH::vec4& dc) {
                L(normal) << "DESATURATE";
                float intensity = 0.3 * c.r + 0.59 * c.g + 0.11 * c.b;
                float k = 0.4;
                dc.r = std::max(std::min((intensity * k + c.r * (1.f - k)), 1.0f), 0.f);
                dc.g = std::max(std::min((intensity * k + c.g * (1.f - k)), 1.0f), 0.f);
                dc.b = std::max(std::min((intensity * k + c.b * (1.f - k)), 1.0f), 0.f);
                dc.a = c.a;
                //return [r, g, b];
            }

        private:
            MATH::vec4 m_previousColor;
            bool m_desaturated;
        };
    }
}

#endif	/* DESATURATEBACKGROUNDONHOVER_H */

