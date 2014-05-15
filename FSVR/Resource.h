/* 
 * File:   Resource.h
 * Author: chris
 *
 * Created on June 9, 2013, 8:36 PM
 */

#ifndef FSVR_RESOURCE_H
#define	FSVR_RESOURCE_H

#include "RID.h"
#include <boost/thread/thread.hpp>

namespace FSVR {
    class Loader;
class Resource {
public:
    enum STATE { INACTIVE, LOADING, RAW, ACTIVE, FAILED };
    enum INSTANTIATION { IMMEDIATELY, ONFIRSTUSE };
public:
    Resource(tRID id);
    virtual ~Resource();

    STATE getState() const;
    void setState(STATE newState);
    
    INSTANTIATION getInstantiation() const { return m_instantiation; }
    void setInstantiation(INSTANTIATION instantiation) { m_instantiation = instantiation; }
    
    Loader* getLoader() const { return m_loader; }
    void setLoader(Loader* loader) { m_loader = loader; }
    
    virtual bool isLoaderToBeDeleted();
    
    tRID getID() const { return m_ID; }
    
    //threading
    inline void lock() { m_mtx.lock(); }
    inline void unlock() { m_mtx.unlock(); }
private:
    tRID m_ID;
    STATE m_state;
    INSTANTIATION m_instantiation;
    Loader* m_loader;
    boost::mutex m_mtx;
};
}
#endif	/* RESOURCE_H */

