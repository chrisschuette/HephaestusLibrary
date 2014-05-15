/* 
 * File:   OpenALSound.h
 * Author: chris
 *
 * Created on March 10, 2014, 6:54 PM
 */

#ifndef OPENALSOUND_H
#define	OPENALSOUND_H

#include <AL/al.h>
#include <AL/alc.h>
#include "../Sound.h"

namespace SND {
    namespace OpenAL {

        class OpenALSound: public SND::Sound {
        public:
            OpenALSound();
            virtual ~OpenALSound();
            
            virtual SND::SoundInstance* createInstance(SYS::Handle<SND::Sound> soundHandle, SND::SoundManager& soundManager);
            ALuint getBuffer() const { return m_buffer; }
        private:
            ALuint m_buffer;
        };
    }
}
#endif	/* OPENALSOUND_H */

