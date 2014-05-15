/* 
 * File:   AppInputMap.h
 * Author: chris
 *
 * Created on June 22, 2013, 3:11 PM
 */

#ifndef APPINPUTMAP_H
#define	APPINPUTMAP_H

#include "INPUT/InputMap.h"

class AppInputMap: public INPUT::InputMap {
public:
    AppInputMap();
    virtual ~AppInputMap();
    virtual void handleInput(const INPUT::Input& input);
    void handleJoystickInput(const INPUT::Input& input);
private:

};

#endif	/* APPINPUTMAP_H */

