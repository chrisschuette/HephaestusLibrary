/* 
 * File:   InputManager.cpp
 * Author: chris
 * 
 * Created on June 22, 2013, 5:06 PM
 */

#include "InputManager.h"
#include "InputMap.h"
#include "../LOG/Core.h"

#include <algorithm>

#define NAME "InputManager"

namespace INPUT {
    std::auto_ptr<InputManager> InputManager::m_pInstance(0);
    
    InputManager::InputManager() {
    }

    InputManager::~InputManager() {
        //L(normal) << "InputManager::~InputManager()";
    }

    InputManager& InputManager::getInstance() {
        //static InputManager inputManager;
        if(m_pInstance.get() == 0) {
            m_pInstance = std::auto_ptr<InputManager>(new InputManager);
        }
        return *m_pInstance;
    }

    void InputManager::processInput(const Input& input) const {
        //std::cout << "Process input" << std::endl;
        //std::cout.flush();
        for(tInputMapList::const_iterator i = m_inputMaps.begin(), e = m_inputMaps.end();
                i != e; ++i)
            (*i)->handleInput(input);
    }

    void InputManager::registerInputMap(InputMap* map) {
        m_inputMaps.push_back(map);
    }

    void InputManager::removeInputMap(InputMap* map) {
        tInputMapList::iterator i = std::find(m_inputMaps.begin(), m_inputMaps.end(), map);
        if(i != m_inputMaps.end())
            m_inputMaps.erase(i);
    }

}
