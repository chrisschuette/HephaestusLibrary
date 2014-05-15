/* 
 * File:   SoundInstance.cpp
 * Author: chris
 * 
 * Created on June 15, 2013, 11:16 AM
 */

#include "SoundInstance.h"
#include "../ERR/ERR.h"
#include "SoundManager.h"

namespace SND {

    SoundInstance::SoundInstance(SYS::Handle<SND::Sound> soundHandle, SoundManager& soundManager)
    : SYS::IsReferenceCounted<SoundInstance>(soundManager)
    , m_soundHandle(soundHandle)
    , m_soundManager(soundManager)
    {

    }
    
    SoundInstance::~SoundInstance() {
    }

    SND::Sound* SoundInstance::getSound() {
        return m_soundHandle.operator *();
    }

}
