/* 
 * File:   Bundle.h
 * Author: chris
 *
 * Created on June 10, 2013, 12:48 AM
 */

#ifndef BUNDLE_H
#define	BUNDLE_H

#include "BID.h"
#include "RID.h"
#include "Location.h"

namespace BNDL {
class Bundle {
public:
    Bundle(tBID id);
    virtual int read(tLocation location, unsigned char ** data) const = 0;
    virtual ~Bundle();
    
    const tBID getID() const { return m_ID; }
    void setID(tBID id) { m_ID = id; }
private:
    tBID m_ID;
};
}
#endif	/* BUNDLE_H */

