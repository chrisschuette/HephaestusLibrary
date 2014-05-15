/* 
 * File:   TextureLoader.cpp
 * Author: chris
 * 
 * Created on June 9, 2013, 8:28 PM
 */

#include "TextureLoader.h"
#include "../DMGD/Resource.h"
#include <IL/il.h>

namespace REND {

    TextureLoader::TextureLoader()
    : DMGD::Loader<REND::Texture>("TextureLoader") {
    }

    TextureLoader::~TextureLoader() {
    }

    void TextureLoader::instantiate(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata) {
        // instantiating a texture means uploading it to the GPU
        DMGD::Resource<REND::Texture>& res = static_cast<DMGD::Resource<REND::Texture>&> (resource);
        res()->upload();
        resource.setState(FSVR::Resource::ACTIVE);
        FSVR::Loader::instantiate(resource, metadata);
        L(normal) << "Resource \"" << resource.getID() << "\" instantiated.";
    }

    void TextureLoader::onLoadComplete(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata) {
        DMGD::Resource<REND::Texture>& res = static_cast<DMGD::Resource<REND::Texture>&> (resource);

        // data: Loader ==> Resource
        REND::Texture* texture = res();
        if (texture) {
            ILuint ImageName; // The image name to return.
            ilGenImages(1, &ImageName); // Grab a new image name.
            ilBindImage(ImageName);
            ilLoadL(IL_TYPE_UNKNOWN, getRawData(), getRawDataSize());
            L(normal) << "w: " << ilGetInteger(IL_IMAGE_WIDTH) << " h: "
                    << ilGetInteger(IL_IMAGE_HEIGHT) << " bpp: " << ilGetInteger(IL_IMAGE_BPP);


            // call base class
            FSVR::Loader::onLoadComplete(resource, metadata);
        }
    }

}