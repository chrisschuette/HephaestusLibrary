/* 
 * File:   OpenALSoundManager.h
 * Author: chris
 *
 * Created on March 10, 2014, 7:51 AM
 */

#ifndef OPENALSOUNDMANAGER_H
#define	OPENALSOUNDMANAGER_H

#include "../SoundManager.h"
#include "../../MEM/Stack.h"
#include "../../MATH/vec234.h"
#include "OpenALSoundLoaderFactory.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>

namespace SND {
    namespace OpenAL {
        class OpenALSoundLoaderFactory;

        namespace OpenALSoundManager_CONST {
            const int MAX_SOURCES = 2;
        }
        class OpenALSoundManager : public SND::SoundManager {
        public:
            OpenALSoundManager(FSVR::FileServer& fileServer);
            virtual ~OpenALSoundManager();
            
            virtual void update(unsigned long int time, unsigned long int diff);
            virtual void unloadUnusedResources();

            virtual SYS::Handle<SND::SoundInstance> getSoundInstance(FSVR::tRID id);

            
            bool acquireSource(ALuint* source);
            bool releaseSource(ALuint source);
            int getActiveSources() const { return m_activeSources; }
            
            // listener
            void setListenerPosition(float x, float y, float z);
            void setListenerVelocity(float v_x, float v_y, float v_z);
            void setListenerOrientation(float f_x, float f_y, float f_z,
                                        float u_x, float u_y, float u_z);
        private:
            bool initOpenAL();
            std::list<std::string> listAllAudioDevices();

            OpenALSoundLoaderFactory m_loaderFactory;
            
            ALCcontext *m_context;
            ALCdevice *m_device;
            bool m_EFX;
            
            MATH::vec3 m_listenerPosition;
            MATH::vec3 m_listenerVelocity;
            MATH::vec6 m_listenerOrientation;
            
            
            ALuint m_sources[OpenALSoundManager_CONST::MAX_SOURCES];
            MEM::Stack<int> m_freeSources;
            int m_activeSources;

            // function pointers
            /* Effect object functions */
            LPALGENEFFECTS alGenEffects;
            LPALDELETEEFFECTS alDeleteEffects;
            LPALISEFFECT alIsEffect;
            LPALEFFECTI alEffecti;
            LPALEFFECTIV alEffectiv;
            LPALEFFECTF alEffectf;
            LPALEFFECTFV alEffectfv;
            LPALGETEFFECTI alGetEffecti;
            LPALGETEFFECTIV alGetEffectiv;
            LPALGETEFFECTF alGetEffectf;
            LPALGETEFFECTFV alGetEffectfv;

            /* Auxiliary Effect Slot object functions */
            LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots;
            LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots;
            LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot;
            LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti;
            LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv;
            LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf;
            LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv;
            LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti;
            LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv;
            LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf;
            LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv;
        };
    }
}
#endif	/* OPENALSOUNDMANAGER_H */

