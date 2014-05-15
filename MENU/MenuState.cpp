/* 
 * File:   MenuState.cpp
 * Author: chris
 * 
 * Created on February 10, 2014, 4:42 PM
 */

#include "MenuState.h"
#include "../INPUT/InputManager.h"
#include "../REND/Renderer.h"
#include <GL/glew.h>

namespace MENU {

    MenuState::MenuState(std::string name, STATE::Context& context, GUI::Theme* theme, GUI::EVENT::EventManager* eventManager)
    : STATE::State(name, context)
    , m_GUI(theme, eventManager) {
    }

    MenuState::~MenuState() {
    }

    void MenuState::OnEnter() {
        INPUT::InputManager::getInstance().registerInputMap(&m_GUI.getEventManager());
    }

    void MenuState::OnLeave() {
        INPUT::InputManager::getInstance().removeInputMap(&m_GUI.getEventManager());
    }

    void MenuState::Update() {
        m_GUI.update();
    }

    void MenuState::Render() {
        m_GUI.render(*this);
    }

}
