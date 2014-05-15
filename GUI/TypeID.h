/* 
 * File:   TypeID.h
 * Author: chris
 *
 * Created on February 10, 2014, 12:02 AM
 */

#ifndef TYPEID_H
#define	TYPEID_H

#include "TypeIDType.h"

namespace GUI {
class TypeID {
public:
    TypeID(tTypeID ID);
    virtual ~TypeID();
    bool operator <(const TypeID& b) const {
        return m_ID < b.m_ID;
    }
    bool operator==(const TypeID& b) const {
        return m_ID == b.m_ID;
    }
    tTypeID getID() const { return m_ID; }
private:
    tTypeID m_ID;
};
}
#endif	/* TYPEID_H */

