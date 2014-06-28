/* 
 * File:   OpenALSoundLoader.h
 * Author: chris
 *
 * Created on March 10, 2014, 6:39 PM
 */

#ifndef OPENALSOUNDLOADER_H
#define	OPENALSOUNDLOADER_H

#include "../../DMGD/Loader.h"
#include "../Sound.h"

namespace SND {
    namespace OpenAL {
        class OpenALSound;
        class OpenALStream;
        class OpenALSoundLoader : public DMGD::Loader<SND::Sound> {
        public:
            OpenALSoundLoader();
            virtual ~OpenALSoundLoader();

            virtual void onLoadComplete(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata);
            virtual void instantiate(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata);
        private:
            void instantiateWave(OpenALSound* openALSound);
            void instantiateOgg(OpenALStream* openALStream);
        };
    }
}
#endif	/* OPENALSOUNDLOADER_H */

