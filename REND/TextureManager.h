/* 
 * File:   TextureManager.h
 * Author: chris
 *
 * Created on March 23, 2014, 3:32 PM
 */

#ifndef TEXTUREMANAGER_H
#define	TEXTUREMANAGER_H

#include "../DMGD/ResourceManager.h"
#include "Texture.h"
#include "../MEM/Pool.h"
#include "../SYS/Reference.h"

namespace REND {
    class TextureManager: public DMGD::ResourceManager<REND::Texture> {
    public:
        TextureManager(DMGD::LoaderFactory<REND::Texture>& loaderFactory, FSVR::FileServer& fileServer);
        virtual ~TextureManager();
        
        // remove abandoned resources;
        virtual void unloadUnusedResources();
        
        virtual void showInfo();
    private:

    };
}
#endif	/* TEXTUREMANAGER_H */

