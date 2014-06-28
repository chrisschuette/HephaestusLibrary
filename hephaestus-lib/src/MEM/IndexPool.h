/* 
 * File:   Pool.h
 * Author: chris
 *
 * Created on June 10, 2013, 9:58 PM
 */

#ifndef INDEXPOOL_H
#define	INDEXPOOL_H

#include "Stack.h"

namespace MEM {
    class IndexPool {
    public:
        IndexPool(int iMaxItems )
        : m_freeIndices( iMaxItems )
        , m_iMaxItems(iMaxItems)
        {
            freeAll();
        }
        unsigned int allocate() {
            unsigned int pItem = m_freeIndices.top();
            m_freeIndices.pop();
            return pItem;
        }
        void free(int index) {
            m_freeIndices.push(index);
        }
        void freeAll() {
            m_freeIndices.clear();
            for(int i = 0; i < m_iMaxItems; i++)
                m_freeIndices.push( i );
        }
        
        int freeIndexCount() { return m_freeIndices.size(); }
    private:
        Stack<unsigned int> m_freeIndices;
        int m_iMaxItems;
    };
}

#endif	/* INDEXPOOL_H */

