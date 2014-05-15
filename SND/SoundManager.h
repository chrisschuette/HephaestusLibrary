/* 
 * File:   SoundManager.h
 * Author: chris
 *
 * Created on June 15, 2013, 11:01 AM
 */

#ifndef SOUNDMANAGER_H
#define	SOUNDMANAGER_H

#include "../LOG/Source.h"
#include "../DMGD/ResourceManager.h"
#include "Sound.h"
#include "../MEM/Pool.h"
#include "../SYS/Reference.h"

namespace SND {
    namespace SoundManager_CONST {
        const int MAX_SOUND_INSTANCES = 32;
    }
    class SoundManager: public DMGD::ResourceManager<SND::Sound>, public MEM::Pool<SYS::Reference<SND::SoundInstance> > {
    public:
        typedef std::list<SoundInstance*> tSoundInstanceList;
    public:
        SoundManager(DMGD::LoaderFactory<SND::Sound>& loaderFactory, FSVR::FileServer& fileServer);
        virtual ~SoundManager();
        
        virtual SYS::Handle<SoundInstance> getSoundInstance(FSVR::tRID id) = 0;
        
        virtual void update() = 0;
        
        // remove abandoned resources;
        virtual void unloadUnusedResources() = 0;
        
        virtual void showInfo();
    protected:
        tSoundInstanceList m_soundInstances;
    };
}
#endif	/* SOUNDMANAGER_H */

