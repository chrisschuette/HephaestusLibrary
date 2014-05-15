/* 
 * File:   Event.cpp
 * Author: chris
 * 
 * Created on February 2, 2014, 7:08 PM
 */

#include "Event.h"

namespace GUI {
    namespace EVENT {
        Event::Event(ID from, ID to, TYPE type)
        : m_from(from)
        , m_to(to)
        , m_type(type)
        {
        }

        Event::~Event() {
        }
    }
}
