/* 
 * File:   SoundManager.cpp
 * Author: chris
 * 
 * Created on June 15, 2013, 11:01 AM
 */

#include "SoundManager.h"
#include "SoundInstance.h"

namespace SND {

    SoundManager::SoundManager(DMGD::LoaderFactory<SND::Sound>& loaderFactory, FSVR::FileServer& fileServer)
    : DMGD::ResourceManager<SND::Sound>(loaderFactory, fileServer)
    , MEM::Pool<SYS::Reference<SND::SoundInstance> >(SoundManager_CONST::MAX_SOUND_INSTANCES) {
    }

    SoundManager::~SoundManager() {
        for (std::list<SND::SoundInstance*>::iterator i = m_soundInstances.begin(),
                e = m_soundInstances.end(); i != e; ++i) {
            SND::SoundInstance* pSoundInstance = (*i);
            delete pSoundInstance;
        }
        m_soundInstances.clear();
    }

    void SoundManager::showInfo() {
        L(normal) << "sounds:";
        L(normal) << "=======";
        DMGD::ResourceManager<SND::Sound>::showResourceInfo();

        L(normal) << "sound instances:";
        L(normal) << "================";

        for (std::list<SND::SoundInstance*>::iterator i = m_soundInstances.begin(),
                e = m_soundInstances.end(); i != e; ++i) {
            SND::SoundInstance* pSoundInstance = (*i);
            SND::Sound* pSound = (*i)->getSound();
            L(normal) << "sound: " << pSound << " ref count: " << pSoundInstance->getReferenceCount();
        }
    }


}
