/* 
 * File:   Pool.h
 * Author: chris
 *
 * Created on June 10, 2013, 9:58 PM
 */

#ifndef POOL_H
#define	POOL_H

#include "Stack.h"

namespace MEM {

    template <class T>
    class Pool {
    public:
        Pool(int iMaxItems )
        : m_freeItems( iMaxItems )
        , m_items( new T[iMaxItems])
        , m_iMaxItems(iMaxItems)
        {
            freeAll();
        }
        ~Pool() {
            delete [] m_items;
        }
        T * allocate() {
            T * pItem = m_freeItems.top();
            m_freeItems.pop();
            return pItem;
        }
        void free(T * pItem) {
            m_freeItems.push(pItem);
        }
        void freeAll() {
            m_freeItems.clear();
            for(int i = 0; i < m_iMaxItems; i++)
                m_freeItems.push( &m_items[i] );
        }
    private:
        Stack<T *> m_freeItems;
        T * m_items;
        int m_iMaxItems;
    };
}

#endif	/* POOL_H */

