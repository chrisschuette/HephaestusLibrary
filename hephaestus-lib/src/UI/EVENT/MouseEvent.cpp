/* 
 * File:   MouseEvent.cpp
 * Author: chris
 * 
 * Created on May 24, 2014, 7:39 PM
 */

#include "MouseEvent.h"

namespace UI {
    namespace EVENT {

        MouseEvent::MouseEvent(MOUSEEVENT_TYPE type) : Event(), m_type(type) {
        }

        MouseEvent::~MouseEvent() {
        }
    }
}
