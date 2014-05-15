/* 
 * File:   GLTextureLoaderFactory.h
 * Author: chris
 *
 * Created on March 23, 2014, 3:57 PM
 */

#ifndef GLTEXTURELOADERFACTORY_H
#define	GLTEXTURELOADERFACTORY_H

#include "../DMGD/LoaderFactory.h"
#include "../REND/Texture.h"

namespace GL {
    class GLTextureLoaderFactory: public DMGD::LoaderFactory<REND::Texture> {
    public:
        GLTextureLoaderFactory();
        virtual ~GLTextureLoaderFactory();

        DMGD::Loader<REND::Texture>* createLoader();
    private:

    };
}

#endif	/* GLTEXTURELOADERFACTORY_H */

