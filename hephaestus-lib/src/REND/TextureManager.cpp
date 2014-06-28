/* 
 * File:   TextureManager.cpp
 * Author: chris
 * 
 * Created on March 23, 2014, 3:32 PM
 */

#include "TextureManager.h"

namespace REND {
    TextureManager::TextureManager(DMGD::LoaderFactory<REND::Texture>& loaderFactory, FSVR::FileServer& fileServer)
    : DMGD::ResourceManager<REND::Texture>(loaderFactory, fileServer)  {
    }

    TextureManager::~TextureManager() {
    }
    
    void TextureManager::showInfo() {
        
    }
    
    void TextureManager::unloadUnusedResources() {
        
    }


}
