/* 
 * File:   AutoTerminator.cpp
 * Author: chris
 * 
 * Created on June 16, 2013, 10:44 PM
 */

#include "AutoTerminator.h"
#include "Terminator.h"
#include "Core.h"

namespace LOG {

AutoTerminator::~AutoTerminator() {
    m_core << LOG::Terminator();
}
}
