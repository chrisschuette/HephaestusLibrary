/* 
 * File:   OpenALSoundInstance.h
 * Author: chris
 *
 * Created on March 10, 2014, 6:55 PM
 */

#ifndef OPENALSOUNDINSTANCE_H
#define	OPENALSOUNDINSTANCE_H

#include "../SoundInstance.h"
#include <AL/al.h>

namespace SND {
    namespace OpenAL {
        class OpenALSoundManager;
        class OpenALSoundInstance: public SND::SoundInstance {
        public:
            OpenALSoundInstance(SYS::Handle<SND::Sound> soundHandle, SND::SoundManager& soundManager);
            virtual ~OpenALSoundInstance();
            
            virtual void play();
            virtual void update();
            virtual bool isPlaying();

        private:
            bool m_playing;
            ALuint m_source;
        };
    }
}
#endif	/* OPENALSOUNDINSTANCE_H */

