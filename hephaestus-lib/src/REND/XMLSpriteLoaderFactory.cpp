/* 
 * File:   XMLSpriteLoaderFactory.cpp
 * Author: chris
 * 
 * Created on June 18, 2014, 11:48 AM
 */

#include "XMLSpriteLoaderFactory.h"
#include "XMLSpriteLoader.h"

namespace REND {

    XMLSpriteLoaderFactory::XMLSpriteLoaderFactory(TextureManager& textureMgr, ShaderManager& shaderMgr)
    : DMGD::LoaderFactory<REND::Sprite>()
    , m_textureMgr(textureMgr)
    , m_shaderMgr(shaderMgr)
    {
    }

    XMLSpriteLoaderFactory::~XMLSpriteLoaderFactory() {
    }

    DMGD::Loader<REND::Sprite>* XMLSpriteLoaderFactory::createLoader() {
        return new XMLSpriteLoader(m_textureMgr, m_shaderMgr);
    }

}
