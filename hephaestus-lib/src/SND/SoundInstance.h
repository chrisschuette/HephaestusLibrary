/* 
 * File:   SoundInstance.h
 * Author: chris
 *
 * Created on June 15, 2013, 11:16 AM
 */

#ifndef SOUNDINSTANCE_H
#define	SOUNDINSTANCE_H

#include "Sound.h"
#include "../SYS/Handle.h"
#include "../SYS/IsReferenceCounted.h"

namespace SND {
    class EventListener;
    class SoundManager;
class SoundInstance: public SYS::IsReferenceCounted<SoundInstance> {
public:
    SoundInstance(SYS::Handle<SND::Sound> soundHandle, SoundManager& soundManager);
    virtual ~SoundInstance();
    
    virtual void play() = 0;
    virtual void update() = 0;
    virtual bool isPlaying() = 0;
    
    SoundManager& getSoundManager() { return m_soundManager; }
    SND::Sound* getSound();
    void setEventListener(EventListener* eventListener) { m_eventListener = eventListener; }
protected:
    SYS::Handle<SND::Sound> m_soundHandle;
    SoundManager& m_soundManager;
    EventListener* m_eventListener;
};
}
#endif	/* SOUNDINSTANCE_H */

