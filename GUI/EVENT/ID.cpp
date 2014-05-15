/* 
 * File:   ID.cpp
 * Author: chris
 * 
 * Created on February 2, 2014, 7:09 PM
 */

#include "ID.h"

namespace GUI {
    namespace EVENT {
        ID::ID() {
        }
        
        ID::ID(tID id) : m_ID(id) {
            
        }
        
        tID ID::operator++(int) {
            return m_ID++;
        }
       
        bool ID::operator<(const ID& rhs) const {
            return (m_ID < rhs.m_ID);
        }

        ID::~ID() {
        }
    }
}
