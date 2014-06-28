/* 
 * File:   SoundLoaderFactory.h
 * Author: chris
 *
 * Created on June 15, 2013, 11:20 AM
 */

#ifndef SOUNDLOADERFACTORY_H
#define	SOUNDLOADERFACTORY_H

#include "Sound.h"
#include "../DMGD/LoaderFactory.h"

namespace SND {
class SoundLoaderFactory: public DMGD::LoaderFactory<SND::Sound> {
public:
    SoundLoaderFactory();
    virtual ~SoundLoaderFactory();
    
    DMGD::Loader<SND::Sound>* createLoader( const DMGD::Resource<SND::Sound>& resource );

private:

};
}
#endif	/* SOUNDLOADERFACTORY_H */

