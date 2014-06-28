/* 
 * File:   SoundLoaderFactory.cpp
 * Author: chris
 * 
 * Created on June 15, 2013, 11:20 AM
 */

#include "SoundLoaderFactory.h"
#include "SoundLoader.h"

namespace SND {

    SoundLoaderFactory::SoundLoaderFactory()
    : DMGD::LoaderFactory<SND::Sound>() {
    }

    SoundLoaderFactory::~SoundLoaderFactory() {
    }

    DMGD::Loader<SND::Sound>* SoundLoaderFactory::createLoader( const DMGD::Resource<SND::Sound>& resource ) {
        return new SND::SoundLoader;
    }

}
