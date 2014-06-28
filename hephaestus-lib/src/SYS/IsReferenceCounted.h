/* 
 * File:   IsReferenceCounted.h
 * Author: chris
 *
 * Created on June 10, 2013, 10:45 PM
 */

#ifndef ISREFERENCECOUNTED_H
#define	ISREFERENCECOUNTED_H

#include "Reference.h"
#include "Handle.h"
#include "../MEM/Pool.h"
#include <iostream>

namespace SYS {

    template<class T>
    class IsReferenceCounted {
    public:

        IsReferenceCounted(MEM::Pool<Reference<T> >& referencePool)
        : m_referencePool(referencePool)
        , m_pReferenceStub(0) {
            m_pReferenceStub = referencePool.allocate();
            if (m_pReferenceStub)
                m_pReferenceStub->setInstance(static_cast<T*> (this));
        }

        IsReferenceCounted(T* instance, MEM::Pool<Reference<T> >& referencePool)
        : m_referencePool(referencePool)
        , m_pReferenceStub(0) {
            m_pReferenceStub = referencePool.allocate();
            if (m_pReferenceStub)
                m_pReferenceStub->setInstance(instance);
        }

        virtual ~IsReferenceCounted() {
            if (m_pReferenceStub) {
                m_pReferenceStub->invalidate();
                if (m_pReferenceStub->getRefCount() == 0)
                    m_referencePool.free(m_pReferenceStub);
                m_pReferenceStub = 0;
            }
        }

        Handle<T>* getHandlePtr() {
            return new Handle<T > (m_pReferenceStub, m_referencePool);
        }

        Handle<T> getHandle() {
            return Handle<T > (m_pReferenceStub, m_referencePool);
        }

        int getReferenceCount() {
            if (m_pReferenceStub)
                return m_pReferenceStub->getRefCount();
            else
                return -1;
        }

        bool setInstance(T* instance) {
            if (m_pReferenceStub)
                m_pReferenceStub->setInstance(instance);
            else
                return false;
            return true;
        }

        T* getInstance() {
            if (m_pReferenceStub)
                return m_pReferenceStub->getInstance();
            else
                return 0;
        }

        const T* getInstance() const {
            if (m_pReferenceStub)
                return m_pReferenceStub->getInstance();
            else
                return 0;
        }

        T* operator()() {
            if (m_pReferenceStub)
                return m_pReferenceStub->getInstance();
            else
                return 0;
        }

    private:
        Reference<T> * m_pReferenceStub;
        MEM::Pool<Reference<T> >& m_referencePool;
    };
}

#endif	/* ISREFERENCECOUNTED_H */

