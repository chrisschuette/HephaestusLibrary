/* 
 * File:   EventListener.h
 * Author: chris
 *
 * Created on June 4, 2014, 9:23 AM
 */

#ifndef FSVREVENTLISTENER_H
#define	FSVREVENTLISTENER_H

namespace FSVR {
    class Resource;
    class EventListener {
    public:
        EventListener() {}
        virtual ~EventListener() {}
        virtual void onLoadComplete(Resource& resource) = 0;
    private:

    };
}

#endif	/* FSVREVENTLISTENER_H */

