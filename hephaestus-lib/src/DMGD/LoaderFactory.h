/* 
 * File:   LoaderFactory.h
 * Author: chris
 *
 * Created on June 9, 2013, 8:11 PM
 */

#ifndef LOADERFACTORY_H
#define	LOADERFACTORY_H

namespace DMGD {
    template <class T>
    class Loader;
    
    template <class T>
    class Resource;
    
template <class T>    
class LoaderFactory {
public:
    LoaderFactory() {}
    virtual ~LoaderFactory() {}

    virtual Loader<T>* createLoader() = 0;
private:

};
}

#endif	/* LOADERFACTORY_H */

