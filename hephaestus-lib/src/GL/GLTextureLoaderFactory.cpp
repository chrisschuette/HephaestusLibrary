/* 
 * File:   GLTextureLoaderFactory.cpp
 * Author: chris
 * 
 * Created on March 23, 2014, 3:57 PM
 */

#include "GLTextureLoaderFactory.h"
#include "GLTextureLoader.h"

namespace GL {
    GLTextureLoaderFactory::GLTextureLoaderFactory() : DMGD::LoaderFactory<REND::Texture>(){
    }

    GLTextureLoaderFactory::~GLTextureLoaderFactory() {
    }
    
    DMGD::Loader<REND::Texture>* GLTextureLoaderFactory::createLoader() {
        return new GLTextureLoader;
    }

}
