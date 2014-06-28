/* 
 * File:   XMLSpriteLoaderFactory.h
 * Author: chris
 *
 * Created on June 18, 2014, 11:48 AM
 */

#ifndef XMLSPRITELOADERFACTORY_H
#define	XMLSPRITELOADERFACTORY_H

#include "../DMGD/LoaderFactory.h"
#include "Sprite.h"

namespace REND {
    class TextureManager;
    class ShaderManager;

    class XMLSpriteLoaderFactory: public DMGD::LoaderFactory<REND::Sprite> {
    public:
        XMLSpriteLoaderFactory(TextureManager& textureMgr, ShaderManager& shaderMgr);
        virtual ~XMLSpriteLoaderFactory();
        
        virtual DMGD::Loader<REND::Sprite>* createLoader();
    private:
        TextureManager& m_textureMgr;
        ShaderManager& m_shaderMgr;
    };
}
#endif	/* XMLSPRITELOADERFACTORY_H */

