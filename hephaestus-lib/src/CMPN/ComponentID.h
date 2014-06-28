/* 
 * File:   ComponentID.h
 * Author: chris
 *
 * Created on August 30, 2013, 2:37 AM
 */

#ifndef COMPONENTID_H
#define	COMPONENTID_H

#include <exception>

namespace CMPN {
   // typedef unsigned int ComponentID;

    class ComponentID {
    public:
        ComponentID() : m_CID(0) {}
        ComponentID(unsigned int index) : m_CID(index+1) {}
        ComponentID& operator=(unsigned int index) {
            m_CID = index+1;
        }
        unsigned int getIndex() const {
            return m_CID-1;
        }
        bool isValid() const { return (m_CID > 0);}
    private:
        unsigned int m_CID;
    };
}

#endif	/* COMPONENTID_H */

