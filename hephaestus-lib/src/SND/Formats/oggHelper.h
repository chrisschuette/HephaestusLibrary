/* 
 * File:   oggHelper.h
 * Author: chris
 *
 * Created on March 11, 2014, 3:47 PM
 */

#ifndef OGGHELPER_H
#define	OGGHELPER_H

#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

namespace SND {
    namespace Formats {

        struct ogg_file {
            unsigned char* curPtr;
            unsigned char* filePtr;
            size_t fileSize;
        };

        size_t AR_readOgg(void* dst, size_t size1, size_t size2, void* fh);
        int AR_seekOgg(void *fh, ogg_int64_t to, int type);
        int AR_closeOgg(void* fh);
        long AR_tellOgg(void *fh);
    }
}
#endif	/* OGGHELPER_H */

