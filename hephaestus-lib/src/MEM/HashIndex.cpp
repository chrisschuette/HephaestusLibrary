/* 
 * File:   HashIndex.cpp
 * Author: chris
 * 
 * Created on March 7, 2014, 11:29 AM
 */

#include "HashIndex.h"
#include "../LOG/Core.h"
#include <assert.h>
#include <cstring>

#define NAME "HashIndex"

namespace MEM {

    HashIndex::HashIndex()
    {
        init(HashIndex_CONST::DEFAULT_HASH_SIZE, HashIndex_CONST::DEFAULT_HASH_SIZE);
    }

    HashIndex::HashIndex(const int initialHashSize, const int initialIndexSize)
    {
        init(initialHashSize, initialHashSize);
    }

    void HashIndex::allocate(const int newHashSize, const int newIndexSize) {
        free();
        m_hashSize = newHashSize;
        m_hash = new int[m_hashSize];
        memset(m_hash, 0xff, m_hashSize * sizeof ( m_hash[0]));
        m_indexSize = newIndexSize;
        m_indexChain = new int[m_indexSize];
        memset(m_indexChain, 0xff, m_indexSize * sizeof ( m_indexChain[0]));
        m_hashMask = m_hashSize - 1;
        m_lookupMask = -1;
    }

    void HashIndex::init(const int initialHashSize, const int initialIndexSize) {
        m_hashSize = initialHashSize;
        m_hash = 0;
        m_indexSize = initialIndexSize;
        m_indexChain = 0;
        m_granularity = HashIndex_CONST::DEFAULT_HASH_GRANULARITY;
        m_hashMask = m_hashSize - 1;
        m_lookupMask = 0;
    }

    void HashIndex::free() {
        if (m_hash != 0) {
            delete[] m_hash;
            m_hash = 0;
        }
        if (m_indexChain != 0) {
            delete[] m_indexChain;
            m_indexChain = 0;
        }
        m_lookupMask = 0;
    }

    HashIndex::~HashIndex() {
        free();
    }

    bool HashIndex::add(const int key, const int index) {
        int h;

        assert(index >= 0);

        if (m_hash == 0)
            allocate(m_hashSize, index >= m_indexSize ? index + 1 : m_indexSize);
        else if (index >= m_indexSize)
            resizeIndex(index + 1);

        h = key & m_hashMask;
        m_indexChain[index] = m_hash[h];
        m_hash[h] = index;
        return true;
    }

    void HashIndex::resizeIndex(const int newIndexSize) {
        int *oldIndexChain, mod, newSize;

        if (newIndexSize <= m_indexSize) {
            return;
        }

        mod = newIndexSize % m_granularity;
        if (!mod) {
            newSize = newIndexSize;
        } else {
            newSize = newIndexSize + m_granularity - mod;
        }

        if (m_indexChain == 0) {
            m_indexSize = newSize;
            return;
        }

        oldIndexChain = m_indexChain;
        m_indexChain = new int[newSize];
        memcpy(m_indexChain, oldIndexChain, m_indexSize * sizeof (int));
        memset(m_indexChain + m_indexSize, 0xff, (newSize - m_indexSize) * sizeof (int));
        delete[] oldIndexChain;
        m_indexSize = newSize;
    }

    int HashIndex::first(const int key) const {
        if(m_hash == 0)
            return -1;
        return m_hash[key & m_hashMask & m_lookupMask];
    }

    int HashIndex::next(const int index) const {
        assert(index >= 0 && index < m_indexSize);
        return m_indexChain[index & m_lookupMask];
    }

    void HashIndex::showHashes() {
        L(normal) << "HASH";
        for (int i = 0; i < m_hashSize; i++)
            L(normal) << i << " " << m_hash[i];
    }

    void HashIndex::showIndices() {
        L(normal) << "INDICES";
        for (int i = 0; i < m_indexSize; i++)
            L(normal) << i << " " << m_indexChain[i];
    }

}
