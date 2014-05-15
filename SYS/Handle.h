/* 
 * File:   Handle.h
 * Author: chris
 *
 * Created on June 10, 2013, 10:09 PM
 */

#ifndef HANDLE_H
#define	HANDLE_H

#include "Reference.h"
#include "../MEM/Pool.h"

#include <iostream>

namespace SYS {

    template<class T>
    class Handle {
    public:

        Handle(Reference<T> * pStub, MEM::Pool<Reference<T> >& pool)
        : m_pReferenceStub(pStub)
        , m_referencePool(pool) {
            if (pStub)
                pStub->addRef();
        }
        
        Handle(const Handle<T>& orig)
        : m_referencePool(orig.m_referencePool)
        , m_pReferenceStub(orig.m_pReferenceStub)
        {
            if(m_pReferenceStub)
                m_pReferenceStub->addRef();
        }

        void setReference(Reference<T> * pStub) {
            if (m_pReferenceStub)
                release();

            m_pReferenceStub = pStub;
            if (pStub)
                pStub->addRef();
        }

        void setReferencePool(MEM::Pool<Reference<T> >* referencePool) {
            m_referencePool = referencePool;
        }

        ~Handle() {
            release();
        }

        void release() {
            if (m_pReferenceStub != 0) {
                m_pReferenceStub->removeRef();
                if ((m_pReferenceStub->getInstance() == 0) &&
                        (m_pReferenceStub->getRefCount() == 0))
                        m_referencePool.free(m_pReferenceStub);
                m_pReferenceStub = 0;
            }
        }

        inline T * operator*() {
            T * pObject = 0;
            if (m_pReferenceStub != 0)
                pObject = m_pReferenceStub->getInstance();
            return pObject;
        }

        inline T * operator->() {
            T * pObject = 0;
            if (m_pReferenceStub != 0)
                pObject = m_pReferenceStub->getInstance();
            return pObject;
        }
        
        inline const T * operator*() const {
            T * pObject = 0;
            if (m_pReferenceStub != 0)
                pObject = m_pReferenceStub->getInstance();
            return pObject;
        }

        inline const T * operator->() const {
            T * pObject = 0;
            if (m_pReferenceStub != 0)
                pObject = m_pReferenceStub->getInstance();
            return pObject;
        }

        Handle<T>& operator=(const Handle<T>& that) {
            if (this != &that) {
                release();
                m_pReferenceStub = that.m_pReferenceStub;
                if (m_pReferenceStub != 0) {
                    if (m_pReferenceStub->getInstance() != 0)
                        m_pReferenceStub->addRef();
                }
            }

            return *this;
        }
    private:
        Reference<T>* m_pReferenceStub;
        MEM::Pool<Reference<T> >& m_referencePool;
    };
}

#endif	/* HANDLE_H */

