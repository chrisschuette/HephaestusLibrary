/* 
 * File:   MouseClickHandler.h
 * Author: chris
 *
 * Created on May 24, 2014, 7:52 PM
 */

#ifndef MOUSECLICKHANDLER_H
#define	MOUSECLICKHANDLER_H

#include "EventHandler.h"
#include "MouseEvent.h"

namespace UI {
    namespace EVENT {

        template <class T>
        class MouseClickHandler : public EventHandler {
        public:
            MouseClickHandler(EventResponder& responder) : EventHandler(responder) {
                
            }
            virtual EVENT::Event::RESULT handleEvent(const Event& e) {
                const MouseEvent& mouseEvent = static_cast<const MouseEvent&> (e);
                if (mouseEvent.getType() == MouseEvent::BUTTONUP) {
                    static_cast<T&>(m_responder).onClick();
                    return EVENT::Event::ACCEPTED;
                }
                return Event::REJECTED;
            }
        };
    }
}
#endif	/* MOUSECLICKHANDLER_H */

