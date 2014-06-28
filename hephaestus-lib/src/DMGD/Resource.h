/* 
 * File:   Resource.h
 * Author: chris
 *
 * Created on June 9, 2013, 8:38 PM
 */

#ifndef DMGD_RESOURCE_H
#define	DMGD_RESOURCE_H

#include "../FSVR/Resource.h"
#include "../SYS/IsReferenceCounted.h"

namespace DMGD {
template <class T>
class Resource: public FSVR::Resource, public SYS::IsReferenceCounted< T > {
public:
    Resource(FSVR::tRID id, MEM::Pool< SYS::Reference< T > >& referencePool) : FSVR::Resource(id), SYS::IsReferenceCounted< T >(0, referencePool)
    {}
    virtual ~Resource() {
        T* data = SYS::IsReferenceCounted< T >::getInstance();
        if( data )
            delete data;
        SYS::IsReferenceCounted< T >::setInstance(0);
    }
private:
};
}
#endif	/* DMGD_RESOURCE_H */

