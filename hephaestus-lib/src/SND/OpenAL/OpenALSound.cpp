/* 
 * File:   OpenALSound.cpp
 * Author: chris
 * 
 * Created on March 10, 2014, 6:54 PM
 */

#include "OpenALSound.h"
#include "OpenALSoundInstance.h"
#include "../../ERR/ERR.h"
#include "../../LOG/Core.h"

#define NAME "OpenALSound"

namespace SND {
    namespace OpenAL {

        OpenALSound::OpenALSound()
        : SND::Sound()
        {
            alGetError();
            alGenBuffers((ALuint) 1, &m_buffer);
            ALCenum err;

            err = alGetError();
            if (err != AL_NO_ERROR) {
                L(error) << "buffer creation failed.";
                THROWS("openal buffer creation failed.");
            }
        }

        OpenALSound::~OpenALSound() {
            alGetError();
            alDeleteBuffers(1, &m_buffer);
            ALCenum err;

            err = alGetError();
            if (err != AL_NO_ERROR) {
                L(error) << "buffer destruction failed.";
                THROWS("openal buffer destruction failed.");
            }
        }

        SND::SoundInstance* OpenALSound::createInstance(SYS::Handle<SND::Sound> soundHandle, SND::SoundManager& soundManager) {
            return new OpenALSoundInstance(soundHandle, soundManager);
        }

    }
}
