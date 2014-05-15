/* 
 * File:   OpenALStream.h
 * Author: chris
 *
 * Created on March 11, 2014, 1:15 PM
 */

#ifndef OPENALSTREAM_H
#define	OPENALSTREAM_H

#include "../Sound.h"

namespace SND {
    class SoundFile;
    namespace OpenAL {

        class OpenALStream : public SND::Sound {
        public:
            enum SOUND_FILE_TYPE {WAVE, OGG};
        public:
            OpenALStream();
            virtual ~OpenALStream();

            virtual SND::SoundInstance* createInstance(SYS::Handle<Sound> soundHandle, SoundManager& soundManager);
            
            SOUND_FILE_TYPE getSoundFileType() const { return m_soundFileType; }
            void setSoundFileType(SOUND_FILE_TYPE soundFileType) { m_soundFileType = soundFileType; }
            
            void setSoundFile(SoundFile* soundFile) { m_soundFile = soundFile; }
            SoundFile* getSoundFile() { return m_soundFile; }
        private:
            SOUND_FILE_TYPE m_soundFileType;
            SoundFile* m_soundFile;
        };
    }
}
#endif	/* OPENALSTREAM_H */

