/* 
 * File:   HashIndex.h
 * Author: chris
 *
 * Created on March 7, 2014, 11:29 AM
 */

#ifndef HASHINDEX_H
#define	HASHINDEX_H

#include "../LOG/Source.h"

namespace MEM {
    namespace HashIndex_CONST {
        const int DEFAULT_HASH_SIZE = 1024;
        const int DEFAULT_HASH_GRANULARITY = 1024;
        const int INVALID_INDEX = -1;
    }

    class HashIndex : public LOG::Source {
    public:
        HashIndex();
        HashIndex(const int initialHashSize, const int initialIndexSize);
        virtual ~HashIndex();

        bool add(const int key, const int index);
        void resizeIndex(const int newIndexSize);

        int first(const int key) const;
        int next(const int index) const;

        // debug
        void showHashes();
        void showIndices();

    private:
        void allocate(const int newHashSize, const int newIndexSize);
        void init(const int initialHashSize, const int initialIndexSize);
        void free();
        int * m_hash;
        int * m_indexChain;
        int m_hashSize;
        int m_indexSize;
        int m_granularity;
        int m_hashMask;
        int m_lookupMask;
    };
}
#endif	/* HASHINDEX_H */

