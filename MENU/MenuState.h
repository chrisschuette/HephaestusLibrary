/* 
 * File:   MenuState.h
 * Author: chris
 *
 * Created on February 10, 2014, 4:42 PM
 */

#ifndef MENUSTATE_H
#define	MENUSTATE_H

#include "../STATE/State.h"
#include "../GUI/THEMES/Default.h"
#include "../GUI/GUI.h"
#include "../GUI/Context.h"
#include "../GUI/EVENT/EventManager.h"

namespace MENU {
class MenuState: public STATE::State, public GUI::Context {
public:
    MenuState(std::string name, STATE::Context& context, GUI::Theme* theme, GUI::EVENT::EventManager* eventManager);
    virtual void OnEnter();
    virtual void OnLeave();
    virtual void Update();
    virtual void Render();
    virtual ~MenuState();
    
    virtual GUI::GUI& getGUI() { return m_GUI; }
private:
    GUI::GUI m_GUI;
};
}
#endif	/* MENUSTATE_H */

