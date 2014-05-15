/* 
 * File:   TextureLoaderFactory.h
 * Author: chris
 *
 * Created on June 9, 2013, 8:17 PM
 */

#ifndef TEXTURELOADERFACTORY_H
#define	TEXTURELOADERFACTORY_H

#include "../DMGD/LoaderFactory.h"
#include "Texture.h"

namespace REND {
class TextureLoaderFactory: public DMGD::LoaderFactory<REND::Texture> {
public:
    TextureLoaderFactory();
    virtual ~TextureLoaderFactory();
   
    virtual DMGD::Loader<REND::Texture>* createLoader( const DMGD::Resource<REND::Texture>& resource );
private:

};
}
#endif	/* TEXTURELOADERFACTORY_H */

