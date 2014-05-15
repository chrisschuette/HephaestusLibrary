/* 
 * File:   EventListener.h
 * Author: chris
 *
 * Created on February 2, 2014, 7:01 PM
 */

#ifndef EVENTLISTENER_H
#define	EVENTLISTENER_H

#include "ID.h"

namespace GUI {
    namespace EVENT {
        class Event;
        class ID;
        class EventListener {
        public:
            EventListener();
            virtual ~EventListener();
            void setID(ID id) { m_ID = id; }
            const ID& getID() const { return m_ID; }
            virtual void handleEvent(const Event& event);
        private:
            ID m_ID;
        };
    }
}
#endif	/* EVENTLISTENER_H */

