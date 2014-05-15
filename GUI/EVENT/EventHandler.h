/* 
 * File:   EventHandler.h
 * Author: chris
 *
 * Created on February 10, 2014, 11:12 AM
 */

#ifndef EVENTHANDLER_H
#define	EVENTHANDLER_H

namespace GUI {
    namespace EVENT {
class EventHandler {
public:
    EventHandler();
    virtual ~EventHandler();
private:

};
        typedef void (EventHandler::*tEventHandler)();
    }
}
#endif	/* EVENTHANDLER_H */

