/* 
 * File:   MainMenuState.h
 * Author: chris
 *
 * Created on February 9, 2014, 4:03 PM
 */

#ifndef MAINMENUSTATE_H
#define	MAINMENUSTATE_H

#include "MENU/MenuState.h"
#include "GL/GUIRenderer.h"
#include "SYS/Handle.h"
#include "SND/SoundInstance.h"

#include "GL/GLSprite.h"
#include "APP/Clock.h"

class ApplicationContext;

class MainMenuState : public MENU::MenuState {
public:
    MainMenuState(STATE::Context& context);
    virtual ~MainMenuState();
    
    virtual void Render();
    virtual void OnEnter();
    virtual void OnLeave();

    static STATE::State* create(STATE::Context& context);
    virtual void OnResize(int width, int height);
    virtual GUI::Renderer& getRenderer() { return m_renderer; }
    
    void NewGameClicked();
    void OptionsClicked();
    void ExitClicked();

private:
    static bool m_Registered;
    ApplicationContext& m_appCtx;
    GL::GUIRenderer m_renderer;
    SYS::Handle<SND::SoundInstance>* m_soundInstance;
    SYS::Handle<SND::SoundInstance>* m_streamInstance;
    GL::GLSprite* m_sprite;
};

#endif	/* MAINMENUSTATE_H */

