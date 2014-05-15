/* 
 * File:   Event.h
 * Author: chris
 *
 * Created on February 2, 2014, 7:08 PM
 */

#ifndef EVENT_H
#define	EVENT_H

#include "ID.h"

namespace GUI {
    namespace EVENT {
        class Event {
        public:
            enum TYPE {
                CLICK
                };
            Event(ID from, ID to, TYPE type);
            virtual ~Event();
            TYPE getType() const { return m_type; }
        protected:
            ID m_from;
            ID m_to;
            TYPE m_type;
        };
    }
}
#endif	/* EVENT_H */

