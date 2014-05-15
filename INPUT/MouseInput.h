/* 
 * File:   MouseInput.h
 * Author: chris
 *
 * Created on February 10, 2014, 12:34 PM
 */

#ifndef MOUSEINPUT_H
#define	MOUSEINPUT_H

#include "Input.h"
#include "../GEOMETRY/Vec2.h"

namespace INPUT {

    class MouseInput : public Input {
    public:

        enum TYPE {
            BUTTONPRESSED, BUTTONRELEASED, MOVED
        };
        HANDLERIDFUNCTIONS
    public:
        MouseInput();
        virtual ~MouseInput();

        inline TYPE getEventType() const {
            return m_eventType;
        }

        inline void setEventType(TYPE eventType) {
            m_eventType = eventType;
        }

        inline void setPosition(int x, int y) {
            m_position.x = x;
            m_position.y = y;
        }
        
        inline const GEOMETRY::Vec2<int>& getPosition() const { return m_position; }
    private:
        TYPE m_eventType;
        GEOMETRY::Vec2<int> m_position;
    };
}
#endif	/* MOUSEINPUT_H */

