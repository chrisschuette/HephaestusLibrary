/* 
 * File:   InputMap.h
 * Author: chris
 *
 * Created on June 22, 2013, 12:56 PM
 */

#ifndef INPUTMAP_H
#define	INPUTMAP_H

#include "id.h"
#include "Hash.h"
#include "Input.h"
#include "../ERR/ERR.h"

#include <typeinfo>
#include <map>
#include <iostream>

namespace INPUT {
    class Input;
class InputMap {
public:
    typedef void (InputMap::*tInputHandler)(const Input&);
    typedef std::map< tID, tInputHandler> tInputHandlerMap;
    InputMap() {}
    virtual ~InputMap() {}
    void registerHandler(tID handlerID, tInputHandler handler);
    void removeHandler(tID handlerID);
    void handleInput(const INPUT::Input& input);
private:
    tInputHandlerMap m_InputHandlerMap;

};
}
#endif	/* INPUTMAP_H */

