/* 
 * File:   OggFile.cpp
 * Author: chris
 * 
 * Created on March 11, 2014, 3:42 PM
 */

#include "OggFile.h"
#include "../../ERR/ERR.h"
#include "../../LOG/Core.h"

#include <string.h>

//#define DEBUG
#define NAME "OggFile"

namespace SND {
    namespace Formats {

        OggFile::OggFile(unsigned char * rawData, unsigned int rawDataSize, bool ownsData)
        : SND::SoundFile("OggFile", rawData, rawDataSize, ownsData) {
            m_t.curPtr = m_t.filePtr = rawData;
            m_t.fileSize = rawDataSize;

            m_ov = new OggVorbis_File;
            memset(m_ov, 0, sizeof ( OggVorbis_File));

            m_callbacks.read_func = AR_readOgg;
            m_callbacks.seek_func = AR_seekOgg;
            m_callbacks.close_func = AR_closeOgg;
            m_callbacks.tell_func = AR_tellOgg;

            int ret = ov_open_callbacks((void *) &m_t, m_ov, NULL, -1, m_callbacks);
            m_vi = ov_info(m_ov, -1); // do I have to free this?
#ifdef DEBUG
            L(normal) << "rate: " << m_vi->rate;
            L(normal) << "bitrate lower: " << m_vi->bitrate_lower;
            L(normal) << "bitrate nominal: " << m_vi->bitrate_nominal;
            L(normal) << "bitrate upper: " << m_vi->bitrate_upper;
            L(normal) << "channels: " << m_vi->channels;
            L(normal) << "version: " << m_vi->version;
#endif
            m_frequency = m_vi->rate;
            m_numChannels = m_vi->channels;
            m_bitsPerSample = m_vi->bitrate_nominal;
        }

        OggFile::~OggFile() {
            ov_clear(m_ov);
            if (m_ov)
                delete m_ov;

        }

        std::string OggFile::errorString(int code) {
            switch (code) {
                case OV_EREAD:
                    return std::string("Read from media.");
                case OV_ENOTVORBIS:
                    return std::string("Not Vorbis data.");
                case OV_EVERSION:
                    return std::string("Vorbis version mismatch.");
                case OV_EBADHEADER:
                    return std::string("Invalid Vorbis header.");
                case OV_EFAULT:
                    return std::string("Internal logic fault (bug or heap/stack corruption.");
                default:
                    return std::string("Unknown Ogg error.");
            }
        }

        int OggFile::read(unsigned char* buffer, unsigned int bytesToRead) {

            int size = 0;
            int section;
            int result;

            while (size < bytesToRead) {
                result = ov_read(m_ov, (char*) (buffer + size), bytesToRead - size, 0, 2, 1, &section);

                if (result > 0)
                    size += result;
                else if (result < 0) {
                    L(error) << errorString(result);
                    return -1;
                } else
                    break;
            }
            return size;

        }

    }
}
