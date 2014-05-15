/* 
 * File:   OpenALSoundLoaderFactory.h
 * Author: chris
 *
 * Created on March 10, 2014, 6:34 PM
 */

#ifndef OPENALSOUNDLOADERFACTORY_H
#define	OPENALSOUNDLOADERFACTORY_H

#include "../../DMGD/LoaderFactory.h"
#include "../Sound.h"

namespace SND {
    namespace OpenAL {
class OpenALSoundLoaderFactory: public DMGD::LoaderFactory<SND::Sound> {
public:
    OpenALSoundLoaderFactory();
    virtual ~OpenALSoundLoaderFactory();
    
    DMGD::Loader<SND::Sound>* createLoader();
private:

};
    }
}
#endif	/* OPENALSOUNDLOADERFACTORY_H */

