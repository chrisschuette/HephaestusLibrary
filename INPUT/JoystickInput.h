/* 
 * File:   JoystickInput.h
 * Author: chris
 *
 * Created on June 22, 2013, 3:10 PM
 */

#ifndef JOYSTICKINPUT_H
#define	JOYSTICKINPUT_H

#include "Input.h"

namespace INPUT {
class JoystickInput: public Input {
public:
    enum TYPE { BUTTONPRESSED, BUTTONRELEASED, MOVED };
HANDLERIDFUNCTIONS
public:
    JoystickInput();
    virtual ~JoystickInput();
    inline TYPE getEventType() const { return m_eventType; }
    inline void setEventType(TYPE eventType) { m_eventType = eventType; }
private:
    TYPE m_eventType;
};
}
#endif	/* JOYSTICKINPUT_H */

