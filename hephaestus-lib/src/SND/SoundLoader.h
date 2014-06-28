/* 
 * File:   SoundLoader.h
 * Author: chris
 *
 * Created on June 15, 2013, 11:19 AM
 */

#ifndef SOUNDLOADER_H
#define	SOUNDLOADER_H

#include "../DMGD/Loader.h"
#include "Sound.h"

namespace SND {

    class SoundLoader : public DMGD::Loader<SND::Sound> {
    public:
        SoundLoader();
        virtual ~SoundLoader();

        void onLoadComplete(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata);
        void instantiate(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata);
    private:

    };
}
#endif	/* SOUNDLOADER_H */

