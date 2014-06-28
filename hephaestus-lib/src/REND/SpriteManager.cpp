/* 
 * File:   SpriteManager.cpp
 * Author: chris
 * 
 * Created on June 18, 2014, 11:30 AM
 */

#include "SpriteManager.h"

namespace REND {
    SpriteManager::SpriteManager(DMGD::LoaderFactory<REND::Sprite>& loaderFactory, FSVR::FileServer& fileServer)
    : DMGD::ResourceManager<REND::Sprite>(loaderFactory, fileServer)
    {
    }

    SpriteManager::~SpriteManager() {
    }
}
