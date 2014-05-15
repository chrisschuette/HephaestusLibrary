/* 
 * File:   Sound.h
 * Author: chris
 *
 * Created on June 15, 2013, 10:59 AM
 */

#ifndef SOUND_H
#define	SOUND_H

#include "../LOG/Source.h"
#include "../SYS/Handle.h"

namespace SND {
    class SoundInstance;
    class SoundManager;
    class Sound: public LOG::Source {
    public:
        Sound();
        virtual ~Sound();
        
        virtual SND::SoundInstance* createInstance(SYS::Handle<Sound> soundHandle, SoundManager& soundManager) = 0;
    private:
    };
}
#endif	/* SOUND_H */

