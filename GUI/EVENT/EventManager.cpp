/* 
 * File:   EventManager.cpp
 * Author: chris
 * 
 * Created on February 2, 2014, 7:22 PM
 */

#include "EventManager.h"
#include "../../INPUT/MouseInput.h"
#include "EventListener.h"
#include "Event.h"


namespace GUI {
    namespace EVENT {
        EventManager::EventManager() : INPUT::InputMap(), LOG::Source("EventManager"), m_currentID(ID(1)), m_designated(ID(0)) {
            registerHandler(HANDLERID(INPUT::MouseInput),static_cast<tInputHandler>(&EventManager::handleMouseInput));
        }

        EventManager::~EventManager() {
        }
        
        void EventManager::addEventListener(EventListener* eventListener) {
            if(eventListener) {
                eventListener->setID(m_currentID);
                std::pair<tEventListenerMap::iterator, bool> result = m_listener.insert(std::pair<ID, EventListener*>(m_currentID, eventListener));
                m_currentID++;
            }
        }
        
        void EventManager::reset() {
            m_listener.clear();
            m_currentID = ID(1);
        }
        
        void EventManager::showInfo() {
            L(normal) << "# of EventListener: " << m_listener.size();
            L(normal) << "currentID: " << m_currentID;
        }
        
        void EventManager::handleMouseInput(const INPUT::Input& input) {
            const INPUT::MouseInput& mouseInput = static_cast<const INPUT::MouseInput&>(input);
            ID componentID = getIDFromPosition(GEOMETRY::Vec2<int>(mouseInput.getPosition()));
            
            switch (mouseInput.getEventType()) {
                case INPUT::MouseInput::MOVED:
                    m_designated = componentID;
                    break;
                case INPUT::MouseInput::BUTTONRELEASED:
                    if(m_designated.isValid()) {
                        tEventListenerMap::iterator i = m_listener.find(m_designated);
                        if(i != m_listener.end()) 
                            (*i).second->handleEvent(EVENT::Event(ID(0), m_designated, EVENT::Event::CLICK));
                    }
                    break;
            }
        }
    }
}
