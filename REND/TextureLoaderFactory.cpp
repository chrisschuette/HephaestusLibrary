/* 
 * File:   TextureLoaderFactory.cpp
 * Author: chris
 * 
 * Created on June 9, 2013, 8:17 PM
 */

#include "TextureLoaderFactory.h"

#include "TextureLoader.h"

namespace REND {
TextureLoaderFactory::TextureLoaderFactory()
: DMGD::LoaderFactory<REND::Texture>() {
}

TextureLoaderFactory::~TextureLoaderFactory() {
}

DMGD::Loader<REND::Texture>* TextureLoaderFactory::createLoader( const DMGD::Resource<REND::Texture>& resource ) {
    return new TextureLoader();
}

}