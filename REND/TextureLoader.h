/* 
 * File:   TextureLoader.h
 * Author: chris
 *
 * Created on June 9, 2013, 8:28 PM
 */

#ifndef TEXTURELOADER_H
#define	TEXTURELOADER_H

#include "Texture.h"
#include "../DMGD/Loader.h"
#include "../FSVR/Resource.h"
#include "../LOG/Source.h"

#include <iostream>

namespace REND {
class TextureLoader : public DMGD::Loader<REND::Texture> {
public:
    TextureLoader();
    virtual ~TextureLoader();

    virtual void onLoadComplete(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata);
    virtual void instantiate(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata);
private:

};
}
#endif	/* TEXTURELOADER_H */

