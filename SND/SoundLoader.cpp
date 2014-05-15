/* 
 * File:   SoundLoader.cpp
 * Author: chris
 * 
 * Created on June 15, 2013, 11:19 AM
 */

#include "SoundLoader.h"
#include "../DMGD/Resource.h"

namespace SND {

    SoundLoader::SoundLoader() : DMGD::Loader<SND::Sound>("SoundLoader") {
    }

    SoundLoader::~SoundLoader() {
    }

    void SoundLoader::onLoadComplete(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata) {
        DMGD::Resource<SND::Sound>& res = static_cast< DMGD::Resource<SND::Sound>& >(resource);
        
        // call base class
        FSVR::Loader::onLoadComplete(resource, metadata);
    }

    void SoundLoader::instantiate(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata) {
        // nothing here
        resource.setState(FSVR::Resource::ACTIVE);
    }
}
