/* 
 * File:   Source.cpp
 * Author: chris
 * 
 * Created on June 12, 2013, 8:05 PM
 */

#include "Source.h"

namespace LOG {
Source::Source(std::string channel)
#ifdef DEBUG
: m_name(channel)
#endif
{
}

Source::~Source() {
}
}