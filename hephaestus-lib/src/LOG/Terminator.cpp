/* 
 * File:   Terminator.cpp
 * Author: chris
 * 
 * Created on June 16, 2013, 9:49 PM
 */

#include "Terminator.h"

namespace LOG {
Terminator::Terminator() {
}

Terminator::~Terminator() {
}

std::ostream& operator<<(std::ostream& stream, const Terminator& arg) {
    return stream;
}

}
