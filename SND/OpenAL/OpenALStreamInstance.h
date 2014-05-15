/* 
 * File:   OpenALStreamInstance.h
 * Author: chris
 *
 * Created on March 11, 2014, 1:18 PM
 */

#ifndef OPENALSTREAMINSTANCE_H
#define	OPENALSTREAMINSTANCE_H

#include "../SoundInstance.h"
#include <AL/al.h>

namespace SND {
    namespace OpenAL {
        namespace OpenALStreamInstance_CONST {
            static const int NUM_BUFFERS = 3;
            static const int BUFFER_SIZE = 4096 * 4;
        }
        class OpenALStreamInstance : public SND::SoundInstance {
        public:
            OpenALStreamInstance(SYS::Handle<SND::Sound> soundHandle, SoundManager& soundManager);
            virtual ~OpenALStreamInstance();

            virtual void play();
            virtual void update();
        private:
            bool refillBuffer(ALuint buffer);
            ALuint m_buffer[OpenALStreamInstance_CONST::NUM_BUFFERS];
            ALuint m_source;
            bool m_playing;
            bool m_streaming;
        };
    }
}
#endif	/* OPENALSTREAMINSTANCE_H */

