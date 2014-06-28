/* 
 * File:   SpriteManager.h
 * Author: chris
 *
 * Created on June 18, 2014, 11:30 AM
 */

#ifndef SPRITEMANAGER_H
#define	SPRITEMANAGER_H

#include "../DMGD/ResourceManager.h"
#include "Sprite.h"

namespace REND {
    class SpriteManager: public DMGD::ResourceManager<REND::Sprite> {
    public:
        SpriteManager(DMGD::LoaderFactory<REND::Sprite>& loaderFactory, FSVR::FileServer& fileServer);
        virtual ~SpriteManager();
    private:

    };
}
#endif	/* SPRITEMANAGER_H */

