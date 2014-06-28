/* 
 * File:   MouseClickToFirstResponder.h
 * Author: chris
 *
 * Created on May 24, 2014, 8:16 PM
 */

#ifndef MOUSECLICKTOFIRSTRESPONDER_H
#define	MOUSECLICKTOFIRSTRESPONDER_H

#include "EventHandler.h"
#include "MouseEvent.h"

#include <iostream>

namespace UI {
    namespace EVENT {

        template <class T>
        class MouseClickToFirstResponder : public EventHandler {
        public:
            MouseClickToFirstResponder(EventResponder& responder) : EventHandler(responder) {
                
            }
            virtual EVENT::Event::RESULT handleEvent(const Event& e) {
                const MouseEvent& mouseEvent = static_cast<const MouseEvent&> (e);
                if (mouseEvent.getType() == MouseEvent::BUTTONUP) {
                    static_cast<Component&>(m_responder).becomeFirstResponder();
                    return EVENT::Event::ACCEPTED;
                }
                return Event::REJECTED;
            }
        };
    }
}
#endif	/* MOUSECLICKTOFIRSTRESPONDER_H */

