/* 
 * File:   OpenALSoundInstance.cpp
 * Author: chris
 * 
 * Created on March 10, 2014, 6:55 PM
 */

#include "OpenALSoundInstance.h"
#include "OpenALSoundManager.h"
#include "OpenALSound.h"
#include "../EventListener.h"
#include <iostream>
#include "../../ERR/ERR.h"
#include "../../LOG/Core.h"
#include "err.h"

#define NAME "OpenALSoundInstance"

namespace SND {
    namespace OpenAL {

        OpenALSoundInstance::OpenALSoundInstance(SYS::Handle<SND::Sound> soundHandle, SND::SoundManager& soundManager)
        : SND::SoundInstance(soundHandle, soundManager)
        , m_playing(false) {
        }

        OpenALSoundInstance::~OpenALSoundInstance() {
            if(m_playing) {
                OpenALSoundManager& mgr = static_cast<OpenALSoundManager&> (m_soundManager);
                alSourceStop(m_source);
                alSourcei(m_source, AL_BUFFER, AL_NONE);
                mgr.releaseSource(m_source);
            }
        }

        void OpenALSoundInstance::update() {
            if (m_playing) {
                ALenum state;
                alGetSourcei(m_source, AL_SOURCE_STATE, &state);
                if(state != AL_PLAYING) {
                    m_playing = false;
                    OpenALSoundManager& mgr = static_cast<OpenALSoundManager&> (m_soundManager);
                    alSourcei(m_source, AL_BUFFER, AL_NONE);
                    mgr.releaseSource(m_source);
                    if(m_eventListener)
                        m_eventListener->onPlaybackEnd(*this);
                }
            }
        }
        
        bool OpenALSoundInstance::isPlaying() {
            return m_playing;
        }


        void OpenALSoundInstance::play() {
            L(normal) << "play";
            if(m_playing)
                return;
            OpenALSound* sound = static_cast<OpenALSound*> (*m_soundHandle);
            OpenALSoundManager& mgr = static_cast<OpenALSoundManager&> (m_soundManager);
            if (sound) {
                // get a source
                if (mgr.acquireSource(&m_source)) {
                    int err;
                    alGetError();
                    alSourcei(m_source, AL_BUFFER, sound->getBuffer());
                    if ((err = alGetError()) != AL_NO_ERROR)
                        THROWS(getALErrorString(err));
                    alSourcePlay(m_source);
                    m_playing = true;
                    if(m_eventListener)
                        m_eventListener->onPlaybackStart(*this);

                    if ((err = alGetError()) != AL_NO_ERROR)
                        THROWS(getALErrorString(err));
                }
            }
        }
    }
}
