/* 
 * File:   hash.h
 * Author: chris
 *
 * Created on February 10, 2014, 12:08 AM
 */

#ifndef HASH_H
#define	HASH_H

#include <boost/functional/hash.hpp>
#include <string>

namespace UTIL {
    unsigned int hash(std::string text);

    template <class T>
    unsigned int getHash(const T& obj) {
         boost::hash<T> hash;
        return hash(obj);
    }
}
#endif	/* HASH_H */

