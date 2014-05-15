/* 
 * File:   AppInputMap.cpp
 * Author: chris
 * 
 * Created on June 22, 2013, 3:11 PM
 */

#include "AppInputMap.h"
#include "INPUT/JoystickInput.h"
#include "ERR/ERR.h"
#include <iostream>

AppInputMap::AppInputMap() : INPUT::InputMap() {
    registerHandler(HANDLERID(INPUT::JoystickInput), static_cast< INPUT::InputMap::tInputHandler >(&AppInputMap::handleJoystickInput));
}

AppInputMap::~AppInputMap() {
}

void AppInputMap::handleInput(const INPUT::Input& input) {
    
}

void AppInputMap::handleJoystickInput(const INPUT::Input& input) {
    const INPUT::JoystickInput& joy = static_cast<const INPUT::JoystickInput&> (input);
    switch (joy.getEventType()) {
        case INPUT::JoystickInput::BUTTONPRESSED:
            std::cout << "Button pressed." << std::endl;
            break;
        case INPUT::JoystickInput::BUTTONRELEASED:
            std::cout << "Button released." << std::endl;
            break;
        case INPUT::JoystickInput::MOVED:
            std::cout << "Joystick moved." << std::endl;
            break;
        default:
            THROWS("Unknown event type.");
    }
}

