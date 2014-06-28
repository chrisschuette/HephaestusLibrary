/* 
 * File:   UI.h
 * Author: chris
 *
 * Created on May 23, 2014, 7:58 PM
 */

#ifndef UI_H
#define	UI_H

#include "View.h"
#include "THEME/Theme.h"
#include "EVENT/EventManager.h"

#define make_connection(component, signal, slot) ( component->signal( boost::bind(&slot, this) ) )

namespace UI {
    class UI: public View {
    public:
        UI();
        virtual ~UI();
        
        virtual void addComponent(Component* component);
        void setTheme(THEME::Theme* theme);
        const THEME::Theme* getTheme() const { return m_theme; }
        EVENT::EventManager& getEventManager() { return m_eventManager; }
        virtual void resize(int x, int y);
    private:
        THEME::Theme* m_theme;
        EVENT::EventManager m_eventManager;
    };
}
#endif	/* UI_H */

