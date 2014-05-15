/* 
 * File:   Button.cpp
 * Author: chris
 * 
 * Created on February 2, 2014, 7:05 PM
 */

#include "Button.h"
#include "../../UTIL/hash.h"
#include "../EVENT/Event.h"
#include <iostream>

namespace GUI {
    namespace COMPONENTS {

        Button::Button()
        : GUI::Component(TypeID(UTIL::hash("Button")))
        , m_buttonText("Default") {
        }

        Button::Button(const std::string buttonText)
        : GUI::Component(TypeID(UTIL::hash("Button")))
        , m_buttonText(buttonText) {
        }

        Button::Button(const std::string* buttonText)
        : GUI::Component(TypeID(UTIL::hash("Button")))
        {
            if(buttonText)
                m_buttonText = *buttonText;
            else
                m_buttonText = "Default";
        }

        Button::~Button() {
        }

        bool Button::click(const click_slot_type& s) {
            boost::signals2::connection c = m_clickedSignal.connect(s);
            if (c.connected())
                return true;
            return false;
        }

        void Button::handleEvent(const EVENT::Event& event) {
            switch (event.getType()) {
                case EVENT::Event::CLICK:
                    m_clickedSignal();
                    break;
            }
        }
    }
}
