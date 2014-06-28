/* 
 * File:   MouseEvent.h
 * Author: chris
 *
 * Created on May 24, 2014, 7:39 PM
 */

#ifndef MOUSEEVENT_H
#define	MOUSEEVENT_H

#include "Event.h"

namespace UI {
    namespace EVENT {

        class MouseEvent: public Event {
        public:
            enum MOUSEEVENT_TYPE { BUTTONDOWN, BUTTONUP, MOVED, MOUSEIN, MOUSEOUT };
        public:
            MouseEvent(MOUSEEVENT_TYPE type);
            virtual ~MouseEvent();
            
            MOUSEEVENT_TYPE getType() const { return m_type; }
        private:
            MOUSEEVENT_TYPE m_type;
        };
    }
}
#endif	/* MOUSEEVENT_H */

