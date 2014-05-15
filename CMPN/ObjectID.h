/* 
 * File:   ObjectID.h
 * Author: chris
 *
 * Created on August 30, 2013, 2:32 AM
 */

#ifndef OBJECTID_H
#define	OBJECTID_H

namespace CMPN {
//    typedef unsigned int ObjectID;
    class ObjectID {
    public:
        ObjectID() : m_OID(0) {}
        ObjectID(unsigned int index) : m_OID(index+1) {}
        ObjectID& operator=(unsigned int index) {
            m_OID = index+1;
        }
        unsigned int getIndex() const {
            return m_OID-1;
        }
        bool isValid() const { return (m_OID > 0);}
        bool operator==(const ObjectID& rhs) const {
            return (rhs.m_OID == m_OID);            
        }
    private:
        unsigned int m_OID;
    };
}

#endif	/* OBJECTID_H */

