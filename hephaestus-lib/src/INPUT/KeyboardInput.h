/* 
 * File:   KeyboardInput.h
 * Author: chris
 *
 * Created on May 27, 2014, 1:36 PM
 */

#ifndef KEYBOARDINPUT_H
#define	KEYBOARDINPUT_H

#include "Input.h"
#include "keycodes.h"

namespace INPUT {

    class KeyboardInput: public Input {
    public:
        enum ACTION { KEYDOWN, KEYUP, KEYREPEAT };
                HANDLERIDFUNCTIONS

    public:
        KeyboardInput();
        virtual ~KeyboardInput();
        
        inline void setAction(ACTION action) { m_action = action; }
        inline void setKey(int key) { m_key = key; }
        
        inline int getKey() const { return m_key; }
        inline ACTION getAction() const { return m_action; }
    private:
        ACTION m_action;
        int m_key;
    };
}
#endif	/* KEYBOARDINPUT_H */

