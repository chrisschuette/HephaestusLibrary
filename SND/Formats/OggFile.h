/* 
 * File:   OggFile.h
 * Author: chris
 *
 * Created on March 11, 2014, 3:42 PM
 */

#ifndef OGGFILE_H
#define	OGGFILE_H

#include "../SoundFile.h"
#include "oggHelper.h"

namespace SND {
    namespace Formats {

        class OggFile: public SND::SoundFile {
        public:
            OggFile(unsigned char * rawData, unsigned int rawDataSize, bool ownsData = true);
            virtual ~OggFile();
            
            virtual int read(unsigned char* buffer, unsigned int bytesToRead);
        private:
            std::string errorString(int code);
            ov_callbacks m_callbacks;
            ogg_file m_t;
            OggVorbis_File* m_ov;
            vorbis_info* m_vi;
        };
    }
}
#endif	/* OGGFILE_H */

