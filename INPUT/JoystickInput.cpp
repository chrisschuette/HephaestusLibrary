/* 
 * File:   JoystickInput.cpp
 * Author: chris
 * 
 * Created on June 22, 2013, 3:10 PM
 */

#include "JoystickInput.h"

namespace INPUT {

    tID JoystickInput::m_handlerID(HANDLERID(JoystickInput));

    JoystickInput::JoystickInput()
    : Input()
    , m_eventType(JoystickInput::BUTTONPRESSED)
    {
    }

    JoystickInput::~JoystickInput() {
    }
}
