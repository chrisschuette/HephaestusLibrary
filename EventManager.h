/* 
 * File:   EventManager.h
 * Author: chris
 *
 * Created on February 12, 2014, 10:23 AM
 */

#ifndef EVENTMANAGER_H
#define	EVENTMANAGER_H

#include "GUI/EVENT/EventManager.h"
#include "GL/GUIRenderer.h"

class EventManager: public GUI::EVENT::EventManager {
public:
    EventManager(GL::GUIRenderer& renderer);
    virtual ~EventManager();
    
    virtual GUI::EVENT::ID getIDFromPosition(const GEOMETRY::Vec2<int>& position);
private:
    GL::GUIRenderer& m_renderer;
};

#endif	/* EVENTMANAGER_H */

