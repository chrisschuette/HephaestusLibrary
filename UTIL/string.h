/* 
 * File:   string.h
 * Author: chris
 *
 * Created on June 17, 2013, 1:05 AM
 */

#ifndef STRING_H
#define	STRING_H

#include <string>
#include <sstream>

namespace UTIL {
    template <class T>
    std::string toString(T value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
}

#endif	/* STRING_H */

