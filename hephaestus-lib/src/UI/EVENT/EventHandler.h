/* 
 * File:   EventHandler.h
 * Author: chris
 *
 * Created on May 24, 2014, 7:23 PM
 */

#ifndef EVENTHANDLER_H
#define	EVENTHANDLER_H

#include "Event.h"

namespace UI {
    namespace EVENT {

        class EventHandler {
        public:
            EventHandler(EventResponder& responder) : m_responder(responder) {}
            virtual EVENT::Event::RESULT handleEvent(const Event& e) {}
        protected:
            EventResponder& m_responder;
        };
    }
}
#endif	/* EVENTHANDLER_H */

