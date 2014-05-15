/* 
 * File:   hash.cpp
 * Author: chris
 * 
 * Created on February 10, 2014, 12:08 AM
 */

#include "hash.h"

namespace UTIL {
    unsigned int hash(std::string text) {
       boost::hash<std::string> string_hash;
        return string_hash(text);
    }
}


