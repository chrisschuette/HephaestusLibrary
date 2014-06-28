/*
 * File:   OpenALSoundManager.cpp
 * Author: chris
 *
 * Created on March 10, 2014, 7:51 AM
 */

#include "OpenALSoundManager.h"
#include "OpenALSoundLoaderFactory.h"
#include "err.h"
#include "../../ERR/ERR.h"
#include "../SoundInstance.h"
#include "../../LOG/Core.h"

#define NAME "OpenALSoundManager"

namespace SND {
    namespace OpenAL {

        OpenALSoundManager::OpenALSoundManager(FSVR::FileServer& fileServer)
        : SND::SoundManager(m_loaderFactory, fileServer)
        , m_device(0)
        , m_context(0)
        , m_EFX(false)
        , m_freeSources(OpenALSoundManager_CONST::MAX_SOURCES)
        , m_activeSources(0) {
            // initialize the driver
            initOpenAL();

            // acquire sources from the driver
            int err;
            alGetError();
            alGenSources(OpenALSoundManager_CONST::MAX_SOURCES, m_sources);
            if ((err = alGetError()) != AL_NO_ERROR)
                THROWS(getALErrorString(err));
            for (int i = 0; i < OpenALSoundManager_CONST::MAX_SOURCES; i++)
                m_freeSources.push(m_sources[i]);


            setListenerPosition(0.0f, 0.0f, 0.0f);
            setListenerVelocity(0.0f, 0.0f, 0.0f);
            setListenerOrientation(0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
        }

        OpenALSoundManager::~OpenALSoundManager() {
            // remove all OpenAL sound buffers before
            // destroying the context and closing the device
            purgeResources();

            for (std::list<SND::SoundInstance*>::iterator i = m_soundInstances.begin(),
                    e = m_soundInstances.end(); i != e; ++i) {
                SND::SoundInstance* pSoundInstance = (*i);
                delete pSoundInstance;
            }
            m_soundInstances.clear();

            // remove the sources
            alDeleteSources(OpenALSoundManager_CONST::MAX_SOURCES, m_sources);

            alcMakeContextCurrent(m_context);
            if (m_context)
                alcDestroyContext(m_context);
            if (m_device)
                alcCloseDevice(m_device);
        }

        void OpenALSoundManager::update(unsigned long int time, unsigned long int diff) {
            // update all sound instances!
            int counter = 0;
            std::list<SND::SoundInstance*>::iterator i = m_soundInstances.begin();
            while (i != m_soundInstances.end()) {
                SND::SoundInstance* pSoundInstance = (*i);
                if (pSoundInstance->getReferenceCount() == 0) {
                    delete pSoundInstance;
                    counter++;
                    i = m_soundInstances.erase(i);
                } else {
                    ++i;
                    pSoundInstance->update();
                }
            }
            if (counter)
                L(normal) << "Cleaned " << counter << " abandoned SoundInstance(s).";

        }

        void OpenALSoundManager::unloadUnusedResources() {

            // clean out all unused sound instances!
            int counter = 0;
            std::list<SND::SoundInstance*>::iterator i = m_soundInstances.begin();
            while (i != m_soundInstances.end()) {
                SND::SoundInstance* pSoundInstance = (*i);
                pSoundInstance->update();
                if (pSoundInstance->getReferenceCount() == 0) {
                    delete pSoundInstance;
                    counter++;
                    i = m_soundInstances.erase(i);
                } else
                    ++i;
            }
            if (counter)
                L(normal) << "Cleaned " << counter << " unused SoundInstance(s).";

            counter = 0;
            for (std::map<FSVR::tRID, DMGD::Resource<SND::Sound>*>::iterator i = m_resourcePtrs.begin(), e = m_resourcePtrs.end();
                    i != e;) {
                DMGD::Resource<SND::Sound>* pResource = (*i).second;
                if (pResource && (pResource->getReferenceCount() == 0)) {
                    counter++;
                    m_resourcePtrs.erase(i++);
                } else
                    ++i;
            }
            if (counter)
                L(normal) << "Cleaned " << counter << " unused Sound(s).";
        }

        SYS::Handle<SND::SoundInstance> OpenALSoundManager::getSoundInstance(FSVR::tRID id) {
            // find the SND::Sound
            DMGD::Resource<SND::Sound>* pResource = getResource(id);
            if (!pResource) {
                L(error) << "Could not find sound " << id;
                return SYS::Handle<SND::SoundInstance>(0, *this);
            } /*else
                L(normal) << "Resource " << id << " found.";*/

            // extract sound from resource
            SND::Sound* pSound = pResource->getInstance();
            if (!pResource) {
                L(error) << "Could not extract sound " << id;
                return SYS::Handle<SND::SoundInstance>(0, *this);
            } /* else
                L(normal) << "Sound " << id << " extracted."; */

            // create a sound instance
            SND::SoundInstance* pSoundInstance = pSound->createInstance(pResource->getHandle(), *this);
            if (!pSoundInstance) {
                L(error) << "Could not create sound instance for sound " << id;
                return SYS::Handle<SND::SoundInstance>(0, *this);
            } /* else
                L(normal) << "Sound instance for sound " << id << " created."; */

            // add to list
            m_soundInstances.push_back(pSoundInstance);

            //return it
            return pSoundInstance->getHandle();
        }

        void OpenALSoundManager::setListenerPosition(float x, float y, float z) {
            int err;
            alGetError();
            m_listenerPosition.data[0] = x;
            m_listenerPosition.data[1] = y;
            m_listenerPosition.data[2] = z;
            alListenerfv(AL_POSITION, m_listenerPosition.data);
            if ((err = alGetError()) != AL_NO_ERROR)
                THROWS(getALErrorString(err));
        }

        void OpenALSoundManager::setListenerVelocity(float v_x, float v_y, float v_z) {
            int err;
            alGetError();
            m_listenerVelocity.data[0] = v_x;
            m_listenerVelocity.data[1] = v_y;
            m_listenerVelocity.data[2] = v_z;
            alListenerfv(AL_VELOCITY, m_listenerVelocity.data);
            if ((err = alGetError()) != AL_NO_ERROR)
                THROWS(getALErrorString(err));
        }

        void OpenALSoundManager::setListenerOrientation(float f_x, float f_y, float f_z,
                float u_x, float u_y, float u_z) {
            int err;
            alGetError();
            // forward
            m_listenerOrientation.data[0] = f_x;
            m_listenerOrientation.data[1] = f_y;
            m_listenerOrientation.data[2] = f_z;
            // up
            m_listenerOrientation.data[3] = u_x;
            m_listenerOrientation.data[4] = u_y;
            m_listenerOrientation.data[5] = u_z;
            alListenerfv(AL_ORIENTATION, m_listenerOrientation.data);
            if ((err = alGetError()) != AL_NO_ERROR)
                THROWS(getALErrorString(err));
        }

        bool OpenALSoundManager::acquireSource(ALuint* source) {
            if (m_freeSources.size() == 0)
                return false;

            *source = m_freeSources.top();
            m_freeSources.pop();
            m_activeSources++;
            return true;
        }

        bool OpenALSoundManager::releaseSource(ALuint source) {
            if (m_freeSources.size() == OpenALSoundManager_CONST::MAX_SOURCES)
                return false;

            m_freeSources.push(source);
            m_activeSources--;
            return true;
        }

        bool OpenALSoundManager::initOpenAL() {

            // check if device enumeration is supported
            ALboolean enumSupported;
            enumSupported = alcIsExtensionPresent(0, "ALC_ENUMERATION_EXT");
            if (enumSupported == AL_FALSE)
                L(normal) << "Device enumeration extension NOT supported.";
            else
                L(normal) << "Device enumeration extension supported.";

            // list audio devices
            if (enumSupported == AL_TRUE) {
                std::list<std::string> audioDevices = listAllAudioDevices();
                L(normal) << "sound devices:";
                L(normal) << "==============";
                int counter = 1;
                for (std::list<std::string>::const_iterator i = audioDevices.begin(),
                        e = audioDevices.end(); i != e; ++i) {
                    L(normal) << counter << ") " << (*i);
                }
            }

            // open default devices
            m_device = alcOpenDevice(NULL);
            if (!m_device) {
                L(error) << "Unable to open audio device.";
                return false;
            } else
                L(normal) << "Audio device successfully opened.";


            // create context
            m_context = alcCreateContext(m_device, NULL);
            if (!alcMakeContextCurrent(m_context)) {
                L(error) << "Unable to create audio context.";
                return false;
            } else
                L(normal) << "Audio context successfully created.";

            // test for EFX extension
            m_EFX = alcIsExtensionPresent(alcGetContextsDevice(alcGetCurrentContext()), "ALC_EXT_EFX");
            if (m_EFX == AL_TRUE) {
                L(normal) << "EFX is supported.";

                // load function pointers
                alGenEffects = (LPALGENEFFECTS) alGetProcAddress("alGenEffects");
                alDeleteEffects = (LPALDELETEEFFECTS) alGetProcAddress("alDeleteEffects");
                alIsEffect = (LPALISEFFECT) alGetProcAddress("alIsEffect");
                alEffecti = (LPALEFFECTI) alGetProcAddress("alEffecti");
                alEffectiv = (LPALEFFECTIV) alGetProcAddress("alEffectiv");
                alEffectf = (LPALEFFECTF) alGetProcAddress("alEffectf");
                alEffectfv = (LPALEFFECTFV) alGetProcAddress("alEffectfv");
                alGetEffecti = (LPALGETEFFECTI) alGetProcAddress("alGetEffecti");
                alGetEffectiv = (LPALGETEFFECTIV) alGetProcAddress("alGetEffectiv");
                alGetEffectf = (LPALGETEFFECTF) alGetProcAddress("alGetEffectf");
                alGetEffectfv = (LPALGETEFFECTFV) alGetProcAddress("alGetEffectfv");

                alGenAuxiliaryEffectSlots = (LPALGENAUXILIARYEFFECTSLOTS) alGetProcAddress("alGenAuxiliaryEffectSlots");
                alDeleteAuxiliaryEffectSlots = (LPALDELETEAUXILIARYEFFECTSLOTS) alGetProcAddress("alDeleteAuxiliaryEffectSlots");
                alIsAuxiliaryEffectSlot = (LPALISAUXILIARYEFFECTSLOT) alGetProcAddress("alIsAuxiliaryEffectSlot");
                alAuxiliaryEffectSloti = (LPALAUXILIARYEFFECTSLOTI) alGetProcAddress("alAuxiliaryEffectSloti");
                alAuxiliaryEffectSlotiv = (LPALAUXILIARYEFFECTSLOTIV) alGetProcAddress("alAuxiliaryEffectSlotiv");
                alAuxiliaryEffectSlotf = (LPALAUXILIARYEFFECTSLOTF) alGetProcAddress("alAuxiliaryEffectSlotf");
                alAuxiliaryEffectSlotfv = (LPALAUXILIARYEFFECTSLOTFV) alGetProcAddress("alAuxiliaryEffectSlotfv");
                alGetAuxiliaryEffectSloti = (LPALGETAUXILIARYEFFECTSLOTI) alGetProcAddress("alGetAuxiliaryEffectSloti");
                alGetAuxiliaryEffectSlotiv = (LPALGETAUXILIARYEFFECTSLOTIV) alGetProcAddress("alGetAuxiliaryEffectSlotiv");
                alGetAuxiliaryEffectSlotf = (LPALGETAUXILIARYEFFECTSLOTF) alGetProcAddress("alGetAuxiliaryEffectSlotf");
                alGetAuxiliaryEffectSlotfv = (LPALGETAUXILIARYEFFECTSLOTFV) alGetProcAddress("alGetAuxiliaryEffectSlotfv");


            } else {
                L(normal) << "EFX is NOT supported.";
                alGenEffects = 0;
                alDeleteEffects = 0;
                alIsEffect = 0;
                alEffecti = 0;
                alEffectiv = 0;
                alEffectf = 0;
                alEffectfv = 0;
                alGetEffecti = 0;
                alGetEffectiv = 0;
                alGetEffectf = 0;
                alGetEffectfv = 0;

                alGenAuxiliaryEffectSlots = 0;
                alDeleteAuxiliaryEffectSlots = 0;
                alIsAuxiliaryEffectSlot = 0;
                alAuxiliaryEffectSloti = 0;
                alAuxiliaryEffectSlotiv = 0;
                alAuxiliaryEffectSlotf = 0;
                alAuxiliaryEffectSlotfv = 0;
                alGetAuxiliaryEffectSloti = 0;
                alGetAuxiliaryEffectSlotiv = 0;
                alGetAuxiliaryEffectSlotf = 0;
                alGetAuxiliaryEffectSlotfv = 0;
            }

            return true;
        }

        std::list<std::string> OpenALSoundManager::listAllAudioDevices() {
            std::list<std::string> devices;
            const ALchar *pDeviceList = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
            if (pDeviceList) {
                while (*pDeviceList) {
                    devices.push_back(pDeviceList);
                    pDeviceList += strlen(pDeviceList) + 1;
                }
            }
            return devices;
        }


    }
}
