/* 
 * File:   OpenALStreamInstance.cpp
 * Author: chris
 * 
 * Created on March 11, 2014, 1:18 PM
 */

#include "OpenALStreamInstance.h"
#include "OpenALSoundManager.h"
#include "err.h"
#include "../../ERR/ERR.h"
#include "OpenALStream.h"
#include "../SoundFile.h"
#include "../EventListener.h"

namespace SND {
    namespace OpenAL {

        OpenALStreamInstance::OpenALStreamInstance(SYS::Handle<SND::Sound> soundHandle, SoundManager& soundManager)
        : SND::SoundInstance(soundHandle, soundManager)
        , m_playing(false)
        , m_streaming(false) {
            int err;
            alGetError();
            alGenBuffers((ALuint) OpenALStreamInstance_CONST::NUM_BUFFERS, m_buffer);
            if ((err = alGetError()) != AL_NO_ERROR) {
                THROWS(getALErrorString(err));
            }
        }

        OpenALStreamInstance::~OpenALStreamInstance() {
            if (m_playing) {
                m_playing = false;
                OpenALSoundManager& mgr = static_cast<OpenALSoundManager&> (m_soundManager);
                alSourceStop(m_source);
                alSourcei(m_source, AL_BUFFER, AL_NONE);
                mgr.releaseSource(m_source);
                return;
            }
            int err;
            alGetError();
            alDeleteBuffers((ALuint) OpenALStreamInstance_CONST::NUM_BUFFERS, m_buffer);
            if ((err = alGetError()) != AL_NO_ERROR) {
                THROWS(getALErrorString(err));
            }
        }

        void OpenALStreamInstance::play() {
            if (m_playing)
                return;
            OpenALSoundManager& mgr = static_cast<OpenALSoundManager&> (m_soundManager);
            // get a source
            if (mgr.acquireSource(&m_source)) {
                for (int i = 0; i < OpenALStreamInstance_CONST::NUM_BUFFERS; i++)
                    if (!refillBuffer(m_buffer[i]))
                        return;

                alSourceQueueBuffers(m_source, OpenALStreamInstance_CONST::NUM_BUFFERS, m_buffer);
                alSourcePlay(m_source);
                m_playing = true;
                m_streaming = true;
                if (m_eventListener)
                    m_eventListener->onPlaybackStart(*this);
            }
        }

        bool OpenALStreamInstance::refillBuffer(ALuint buffer) {
            unsigned char pcm[OpenALStreamInstance_CONST::BUFFER_SIZE];
            int size = 0;
            int section;
            int result;

            SND::OpenAL::OpenALStream* pStream = static_cast<SND::OpenAL::OpenALStream*> (*m_soundHandle);
            if (pStream) {
                SND::SoundFile* pSoundFile = pStream->getSoundFile();
                if (pSoundFile) {
                    size = pSoundFile->read(pcm, OpenALStreamInstance_CONST::BUFFER_SIZE);
                    if (size <= 0)
                        return false;
                    alBufferData(buffer, (pSoundFile->getNumChannels() == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16), pcm, size, pSoundFile->getFrequency());
                } else
                    return false;
            } else
                return false;

            return true;
        }
        
        bool OpenALStreamInstance::isPlaying() {
            return m_playing;
        }


        void OpenALStreamInstance::update() {
            if (m_playing) {
                ALenum state;
                alGetSourcei(m_source, AL_SOURCE_STATE, &state);
                if (state != AL_PLAYING) {
                    m_playing = false;
                    OpenALSoundManager& mgr = static_cast<OpenALSoundManager&> (m_soundManager);
                    alSourcei(m_source, AL_BUFFER, AL_NONE);
                    mgr.releaseSource(m_source);
                    if (m_eventListener)
                        m_eventListener->onPlaybackEnd(*this);
                    return;
                }
                if (m_streaming) {
                    int processed;
                    bool active = true;

                    alGetSourcei(m_source, AL_BUFFERS_PROCESSED, &processed);

                    while (processed--) {
                        ALuint buffer;

                        alSourceUnqueueBuffers(m_source, 1, &buffer);

                        active = refillBuffer(buffer);
                        if (!active) {
                            m_streaming = false;
                        } else {
                            alSourceQueueBuffers(m_source, 1, &buffer);
                        }
                    }
                }
            }
        }
    }
}
