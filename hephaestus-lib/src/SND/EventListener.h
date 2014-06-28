/* 
 * File:   EventListener.h
 * Author: chris
 *
 * Created on June 3, 2014, 11:39 PM
 */

#ifndef EVENTLISTENER_H
#define	EVENTLISTENER_H

namespace SND {
    class SoundInstance;
    class EventListener {
    public:
        EventListener();
        virtual ~EventListener();
        
        virtual void onPlaybackStart(SND::SoundInstance& instance) {}
        virtual void onPlaybackEnd(SND::SoundInstance& instance) {}
    private:

    };
}

#endif	/* EVENTLISTENER_H */

