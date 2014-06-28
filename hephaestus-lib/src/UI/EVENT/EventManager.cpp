/* 
 * File:   EventManager.cpp
 * Author: chris
 * 
 * Created on May 24, 2014, 5:50 PM
 */

#include "EventManager.h"
#include "../../INPUT/MouseInput.h"
#include "MouseEvent.h"
#include "../UI.h"
#include "../../LOG/Core.h"

#define NAME "EventManager"

namespace UI {
    namespace EVENT {

        EventManager::EventManager(UI& ui) : INPUT::InputMap(), m_UI(ui), m_firstResponder(0), m_hoverComponent(0) {
            registerHandler(HANDLERID(INPUT::MouseInput), static_cast<tInputHandler> (&EventManager::handleMouseInput));
        }

        EventManager::~EventManager() {
        }

        void EventManager::handleMouseInput(const INPUT::Input& input) {
            const INPUT::MouseInput& mouseInput = static_cast<const INPUT::MouseInput&> (input);
            Component* c;
            switch (mouseInput.getEventType()) {
                case INPUT::MouseInput::BUTTONPRESSED:
                    c = m_UI.getComponent(m_mousePosition);
                    while (c != 0) {
                        if (c->handleEvent(MouseEvent(MouseEvent::BUTTONUP)) == Event::CONSUMED)
                            break;
                        c = c->getParent();
                    }
                    break;
                case INPUT::MouseInput::MOVED:
                    const MATH::ivec2& position = mouseInput.getPosition();
                    m_mousePosition.x = position.x;
                    m_mousePosition.y = position.y;
                    c = m_UI.getComponent(m_mousePosition);
                    if (c && c != m_hoverComponent) {
                        if (m_hoverComponent)
                            m_hoverComponent->handleEvent(MouseEvent(MouseEvent::MOUSEOUT));
                        m_hoverComponent = c;
                        m_hoverComponent->handleEvent(MouseEvent(MouseEvent::MOUSEIN));
                    }
                    break;
            }
        }

    }
}
