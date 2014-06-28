/* 
 * File:   KeyboardInput.cpp
 * Author: chris
 * 
 * Created on May 27, 2014, 1:36 PM
 */

#include "KeyboardInput.h"

namespace INPUT {
    tID KeyboardInput::m_handlerID(HANDLERID(KeyboardInput));

    KeyboardInput::KeyboardInput() : INPUT::Input() {
    }

    KeyboardInput::~KeyboardInput() {
    }
}
