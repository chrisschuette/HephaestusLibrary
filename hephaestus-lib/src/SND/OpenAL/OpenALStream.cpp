/* 
 * File:   OpenALStream.cpp
 * Author: chris
 * 
 * Created on March 11, 2014, 1:15 PM
 */

#include "OpenALStream.h"
#include "OpenALStreamInstance.h"
#include "../SoundFile.h"

namespace SND {
    namespace OpenAL {
        OpenALStream::OpenALStream()
        : SND::Sound()
        , m_soundFileType(OGG)
        , m_soundFile(0)
        {
        }

        OpenALStream::~OpenALStream() {
            if(m_soundFile)
                delete m_soundFile;
        }
        
        SND::SoundInstance* OpenALStream::createInstance(SYS::Handle<Sound> soundHandle, SoundManager& soundManager) {
            return new OpenALStreamInstance(soundHandle, soundManager);
        }
    }
}
