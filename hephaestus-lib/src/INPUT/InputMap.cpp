#include "InputMap.h"
#include "../UTIL/string.h"

namespace INPUT {
    void InputMap::registerHandler(tID handlerID, tInputHandler handler) {
        m_InputHandlerMap.insert(std::pair<tID, tInputHandler>(handlerID, handler));
    }
    void InputMap::handleInput(const INPUT::Input& input) {
        tInputHandlerMap::const_iterator i = m_InputHandlerMap.find(input.getHandlerID());
        if(i == m_InputHandlerMap.end())
            return; // no error - just do nothing
        tInputHandler handler = (*i).second;
        // call the handler function pointer
        ((*this).*handler)(input);
    }
    void InputMap::removeHandler(tID handlerID) {
        tInputHandlerMap::iterator i = m_InputHandlerMap.find(handlerID);
        if(i != m_InputHandlerMap.end())
            m_InputHandlerMap.erase(i);
        else
            THROWS("Unknown handler: " + UTIL::toString(handlerID));
    }
}