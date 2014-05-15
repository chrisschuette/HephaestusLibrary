/* 
 * File:   EventManager.cpp
 * Author: chris
 * 
 * Created on February 12, 2014, 10:23 AM
 */

#include "EventManager.h"

EventManager::EventManager(GL::GUIRenderer& renderer)
: GUI::EVENT::EventManager()
, m_renderer(renderer)
{
}

EventManager::~EventManager() {
}

GUI::EVENT::ID EventManager::getIDFromPosition(const GEOMETRY::Vec2<int>& position) {
    // determine ID from stencil buffer
    // invert y
      unsigned int index = m_renderer.readPixelFromStencilBuffer(GEOMETRY::Vec2<int>(position.x, m_renderer.getScreenHeight() - position.y - 1));
      
      return GUI::EVENT::ID(index);
}

