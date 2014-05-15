/* 
 * File:   Reference.h
 * Author: chris
 *
 * Created on June 10, 2013, 10:09 PM
 */

#ifndef REFERENCE_H
#define	REFERENCE_H

#include <iostream>

namespace SYS {
    template <class T>
    class Reference {
    public:
        Reference()
        : m_pInstance(0)
        , m_iRefCount(0)
        {}
        Reference( T * pInstance )
        : m_pInstance(pInstance)
        , m_iRefCount(0)
        {}
        ~Reference() {
            m_pInstance = 0; // ???
        }
        const T * getInstance() const {
            return m_pInstance;
        }
        void setInstance(T * instance) {
            m_pInstance = instance;
        }
        T * getInstance() {
            return m_pInstance;
        }
        void addRef() {
            ++m_iRefCount;
        }
        void removeRef() {
            --m_iRefCount;
        }
        int getRefCount() {
            return m_iRefCount;
        }
        void invalidate() {
            m_pInstance = 0;
        }
    private:
        T * m_pInstance;
        int m_iRefCount;
    };
}

#endif	/* REFERENCE_H */

