/* 
 * File:   EventManager.h
 * Author: chris
 *
 * Created on May 24, 2014, 5:50 PM
 */

#ifndef EVENTMANAGER_H
#define	EVENTMANAGER_H

#include "../../INPUT/InputMap.h"
#include "../../MATH/vec234.h"

#include <iostream>

namespace UI {
    class UI;
    class Component;
    namespace EVENT {
        class EventResponder;
        class EventManager: public INPUT::InputMap {
        public:
            EventManager(UI& m_UI);
            virtual ~EventManager();
            
            void handleMouseInput(const INPUT::Input& input);
            void setFirstResponder(EventResponder* c) {
                m_firstResponder = c;
            }
        private:
            UI& m_UI;
            MATH::ivec2 m_mousePosition;
            EventResponder* m_firstResponder;
            Component* m_hoverComponent;
        };
    }
}
#endif	/* EVENTMANAGER_H */

