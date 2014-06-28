/* 
 * File:   GLTextureLoader.cpp
 * Author: chris
 * 
 * Created on March 23, 2014, 3:53 PM
 */

#include "GLTextureLoader.h"
#include "../FSVR/ResourceMetaData.h"
#include "../DMGD/Resource.h"
#include "GLTexture.h"
#include "../ERR/ERR.h"
#include "../LOG/Core.h"
#include <IL/il.h>
#include <IL/ilu.h>

#define NAME "GLTextureLoader"

namespace GL {

    GLTextureLoader::GLTextureLoader() : DMGD::Loader<REND::Texture>() {
    }

    GLTextureLoader::~GLTextureLoader() {
    }

    void GLTextureLoader::onLoadComplete(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata) {
        
        if(resource.getInstantiation() == FSVR::Resource::IMMEDIATELY)
            THROWS("Immediate instantiation not supported for textures.");

        DMGD::Resource<REND::Texture>& res = static_cast<DMGD::Resource<REND::Texture>&> (resource);

        // read out metadata and create payload class
        if (metadata.getType() != "texture")
            THROWS("Resource is not a a texture: type = " + metadata.getType());
        GLTexture* texture = new GLTexture;

        // raw data ==> DevIL
        texture->loadImageData(getRawData(), getRawDataSize());
        
        // free raw data
        discardRawData();
        
        // set texture in resource
        res.setInstance(texture);

        // decide about instantiation
        FSVR::Loader::onLoadComplete(resource, metadata);
    }

    void GLTextureLoader::instantiate(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata) {
        DMGD::Resource<REND::Texture>& res = static_cast<DMGD::Resource<REND::Texture>&> (resource);
        GLTexture* texture = static_cast<GLTexture*>(res());
                
        // DevIL ==> GPU
        if(!texture->upload())
            THROWS("Upload to GPU failed.");

        // mark as active
        FSVR::Loader::instantiate(resource, metadata);
    }
}
