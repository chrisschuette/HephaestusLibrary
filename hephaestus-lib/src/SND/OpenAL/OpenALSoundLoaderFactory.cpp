/* 
 * File:   OpenALSoundLoaderFactory.cpp
 * Author: chris
 * 
 * Created on March 10, 2014, 6:34 PM
 */

#include "OpenALSoundLoaderFactory.h"
#include "OpenALSoundLoader.h"

namespace SND {
    namespace OpenAL {
OpenALSoundLoaderFactory::OpenALSoundLoaderFactory()
: DMGD::LoaderFactory<SND::Sound>()
{
}

OpenALSoundLoaderFactory::~OpenALSoundLoaderFactory() {
}

DMGD::Loader<SND::Sound>* OpenALSoundLoaderFactory::createLoader() {
    return new OpenALSoundLoader;
}


    }
}
