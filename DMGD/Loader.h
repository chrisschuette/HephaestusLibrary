/* 
 * File:   Loader.h
 * Author: chris
 *
 * Created on June 9, 2013, 8:08 PM
 */

#ifndef DMGD_LOADER_H
#define	DMGD_LOADER_H

#include "../FSVR/Loader.h"

namespace DMGD {
template <class T>
class Loader: public FSVR::Loader {
public:
    Loader(std::string type) : FSVR::Loader(type) {}
    virtual ~Loader() {}
private:

};
}

#endif	/* DMGD_LOADER_H */

