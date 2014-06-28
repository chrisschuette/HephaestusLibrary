/* 
 * File:   Event.h
 * Author: chris
 *
 * Created on May 24, 2014, 7:27 PM
 */

#ifndef EVENT_H
#define	EVENT_H

namespace UI {
    namespace EVENT {

        class Event {
        public:
                enum RESULT { ACCEPTED, REJECTED, CONSUMED };
        public:
            Event();
            virtual ~Event();
        private:

        };
    }
}
#endif	/* EVENT_H */

