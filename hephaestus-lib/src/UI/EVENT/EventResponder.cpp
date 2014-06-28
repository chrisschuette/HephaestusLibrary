/* 
 * File:   EventResponder.cpp
 * Author: chris
 * 
 * Created on May 24, 2014, 7:21 PM
 */

#include "EventResponder.h"
#include "EventHandler.h"

namespace UI {
    namespace EVENT {

        EventResponder::EventResponder() {
        }

        EventResponder::~EventResponder() {
            for( std::list<EventHandler*>::iterator i = m_handlers.begin(), e = m_handlers.end(); i != e; ++i )
                delete (*i);
        }

        void EventResponder::addEventHandler(EventHandler* handler) {
            m_handlers.push_back(handler);
        }

        void EventResponder::removeEventHandler(EventHandler* handler) {
            std::list<EventHandler*>::iterator i = m_handlers.begin();
            while (i != m_handlers.end()) {
                if ((*i) == handler)
                    m_handlers.erase(i++);
                else
                    ++i;
            }
        }

        Event::RESULT EventResponder::handleEvent(const Event& event) {
           Event::RESULT result = Event::REJECTED;
            // see if the event handlers want it
            for (std::list<EventHandler*>::const_iterator i = m_handlers.begin(),
                    e = m_handlers.end(); i != e; ++i) {
                Event::RESULT r = (*i)->handleEvent(event);
                if(r == Event::CONSUMED)
                    return r;
                else if(r == Event::ACCEPTED)
                    result = Event::CONSUMED;
            }
            return result;
        }
    }
}
