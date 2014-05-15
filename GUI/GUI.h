/* 
 * File:   GUI.h
 * Author: chris
 *
 * Created on February 2, 2014, 7:17 PM
 */

#ifndef GUI_H
#define	GUI_H

#include "EVENT/EventManager.h"
#include "Container.h"
#include <list>
#include <boost/bind.hpp>

#define make_connection(component, signal, slot) ( component->signal( boost::bind(&slot, this) ) )

namespace GUI {
    namespace EVENT {
        class EventManager;
    }
    class Context;
    class Component;
    class Theme;
    class GUI: public Container {
    public:
        GUI(Theme* theme, EVENT::EventManager* eventManager);
        virtual ~GUI();
        virtual void update();
        virtual void render(VIEW::Context& pContext) const;
        virtual void addComponent(Component * pChild, Context& ctx);
        EVENT::EventManager& getEventManager();
        
        // disable View
        virtual void addChild(VIEW::Element * pChild);
        virtual void removeChild(VIEW::Element * pChild);
        virtual void removeAllChildren();
    private:
        Theme* m_theme;
        EVENT::EventManager* m_eventMgr;
    };
}
#endif	/* GUI_H */

