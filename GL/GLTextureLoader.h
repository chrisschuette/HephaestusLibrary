/* 
 * File:   GLTextureLoader.h
 * Author: chris
 *
 * Created on March 23, 2014, 3:53 PM
 */

#ifndef GLTEXTURELOADER_H
#define	GLTEXTURELOADER_H

#include "../DMGD/Loader.h"
#include "../REND/Texture.h"

namespace GL {
    class GLTextureLoader: public DMGD::Loader<REND::Texture> {
    public:
        GLTextureLoader();
        virtual ~GLTextureLoader();
        
        virtual void onLoadComplete(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata);
        virtual void instantiate(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata);
    private:

    };
}
#endif	/* GLTEXTURELOADER_H */

