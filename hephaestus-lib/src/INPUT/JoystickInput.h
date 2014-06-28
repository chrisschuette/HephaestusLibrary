/* 
 * File:   JoystickInput.h
 * Author: chris
 *
 * Created on May 27, 2014, 9:57 AM
 */

#ifndef JOYSTICKINPUT_H
#define	JOYSTICKINPUT_H

#include "Input.h"

namespace INPUT {

    class JoystickInput: public INPUT::Input {
    public:
        enum INPUT_TYPE { BUTTONDOWN, BUTTONUP, AXESUPDATE };
        HANDLERIDFUNCTIONS
    public:
        JoystickInput();
        virtual ~JoystickInput();
        
        // getters & setters
        void setInputType(INPUT_TYPE type) { m_type  = type; }
        INPUT_TYPE getInputType() const { return m_type; }
        void setAxes(int noOfAxes);
        
        void updateAxesValues(const float* axesValues);
        inline const float& getAxesValue(int axes) const { return m_axesValues[axes]; }
    private:
        INPUT_TYPE m_type;
        float* m_axesValues;
        int m_axes;
    };
}

#endif	/* JOYSTICKINPUT_H */

