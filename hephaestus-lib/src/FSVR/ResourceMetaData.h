/* 
 * File:   ResourceMetaData.h
 * Author: chris
 *
 * Created on June 10, 2013, 1:19 AM
 */

#ifndef RESOURCEMETADATA_H
#define	RESOURCEMETADATA_H

#include "../BNDL/BID.h"
#include "RID.h"
#include "RType.h"
#include "../BNDL/Location.h"
#include "../BNDL/RID.h"

namespace FSVR {
class ResourceMetaData {
public:
    ResourceMetaData();
    virtual ~ResourceMetaData();
    
    void setBundleID(BNDL::tBID bid) { m_bundleID = bid; }
    void setResourceID(BNDL::tRID rid) { m_resourceID = rid; }
    void setLocation(BNDL::tLocation location) { m_location = location; }
    void setType(tRTYPE type) { m_type = type; }
    
    const BNDL::tBID getBundleID() const { return m_bundleID; } 
    const BNDL::tRID getResourceID() const { return m_resourceID; }
    const BNDL::tLocation getLocation() const { return m_location; }
    const tRTYPE getType() const { return m_type; }
    virtual const char* getValue(const char* key) const { return 0; }
private:
    tRID m_ID;
    BNDL::tBID m_bundleID;
    BNDL::tRID m_resourceID;
    BNDL::tLocation m_location;
    tRTYPE m_type;
};
}
#endif	/* RESOURCEMETADATA_H */

