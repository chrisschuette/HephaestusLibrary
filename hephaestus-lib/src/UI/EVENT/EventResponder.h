/* 
 * File:   EventResponder.h
 * Author: chris
 *
 * Created on May 24, 2014, 7:21 PM
 */

#ifndef EVENTRESPONDER_H
#define	EVENTRESPONDER_H

#include <list>

#include "Event.h"

namespace UI {
    namespace EVENT {
        class Event;
        class EventHandler;
        class EventResponder {
        public:
            EventResponder();
            virtual ~EventResponder();
            
            void addEventHandler(EventHandler* handler);
            void removeEventHandler(EventHandler* handler);
            
            Event::RESULT handleEvent(const Event& event);
        private:
            std::list<EventHandler*> m_handlers;
        };
    }
}
#endif	/* EVENTRESPONDER_H */

