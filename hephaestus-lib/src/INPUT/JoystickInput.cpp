/* 
 * File:   JoystickInput.cpp
 * Author: chris
 * 
 * Created on May 27, 2014, 9:57 AM
 */

#include "JoystickInput.h"
#include <string.h>

namespace INPUT {
    tID JoystickInput::m_handlerID(HANDLERID(JoystickInput));

    JoystickInput::JoystickInput() : INPUT::Input(), m_axesValues(0), m_axes(0) {

    }

    void JoystickInput::setAxes(int noOfAxes) {
        if (m_axesValues)
            delete [] m_axesValues;
        m_axesValues = new float[noOfAxes];
        m_axes = noOfAxes;
    }

    JoystickInput::~JoystickInput() {
        if (m_axesValues)
            delete [] m_axesValues;
    }
    
    void JoystickInput::updateAxesValues(const float* axesValues) {
        memcpy(m_axesValues, axesValues, sizeof(float) * m_axes);
    }


}
