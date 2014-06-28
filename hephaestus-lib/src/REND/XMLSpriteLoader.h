/* 
 * File:   XMLSpriteLoader.h
 * Author: chris
 *
 * Created on June 18, 2014, 11:36 AM
 */

#ifndef XMLSPRITELOADER_H
#define	XMLSPRITELOADER_H

#include "../DMGD/Loader.h"
#include "Sprite.h"
#include "../REND/GradientSprite.h"

namespace REND {
    class ShaderManager;
    class TextureManager;

    class XMLSpriteLoader : public DMGD::Loader<REND::Sprite> {
    public:
        struct GradientStop {
            MATH::vec4 color;
            float position;
        };
    public:
        XMLSpriteLoader(TextureManager& textureMgr, ShaderManager& shaderMgr);
        virtual ~XMLSpriteLoader();

        virtual void onLoadComplete(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata);
        virtual void instantiate(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata);
        REND::Sprite* createSprite(const FSVR::ResourceMetaData& metadata);
        REND::Sprite* createGradientSprite(const FSVR::ResourceMetaData& metadata);
        REND::Sprite* createAnimatedSprite(const FSVR::ResourceMetaData& metadata);

    private:
        char* m_XML;
        TextureManager& m_textureMgr;
        ShaderManager& m_shaderMgr;
    };
}
#endif	/* XMLSPRITELOADER_H */

