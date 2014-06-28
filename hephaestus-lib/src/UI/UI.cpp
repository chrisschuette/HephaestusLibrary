/* 
 * File:   UI.cpp
 * Author: chris
 * 
 * Created on May 23, 2014, 7:58 PM
 */

#include "UI.h"
#include "THEME/Theme.h"
#include <assert.h>
#include "../INPUT/InputManager.h"

namespace UI {

    UI::UI() : View("UI"), m_theme(0), m_eventManager(*this) {
        setUI(this);
        INPUT::InputManager::getInstance().registerInputMap(&m_eventManager);
    }

    UI::~UI() {
        if (m_theme)
            delete m_theme;
        INPUT::InputManager::getInstance().removeInputMap(&m_eventManager);

    }

    void UI::addComponent(Component* component) {
        assert(component);
        m_children.push_back(component);
        setParent(*component, this);
        component->setUI(this);
    }

    void UI::setTheme(THEME::Theme* theme) {
        m_theme = theme;
    }

    void UI::resize(int x, int y) {
        Component::resize(x,y);
        setContainerDimensions(x - 2 * getHPadding(),y - 2 * getVPadding());
    }
}
