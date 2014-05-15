/* 
 * File:   MainMenuState.cpp
 * Author: chris
 * 
 * Created on February 9, 2014, 4:03 PM
 */

#include "MainMenuState.h"
#include "GUI/COMPONENTS/Button.h"
#include "StateManager.h"
#include "GUI/LAYOUT/Vertical.h"
#include "ApplicationContext.h"
#include "EventManager.h"
#include "SND/OpenAL/OpenALSoundManager.h"
#include "REND/FONTS/FontManager.h"
#include "REND/TextureManager.h"
#include "LOC/LangDict.h"
#include "REND/ShaderManager.h"
#include "UTIL/string.h"

bool MainMenuState::m_Registered = StateManager::getInstance().Register("MainMenu", &MainMenuState::create);

MainMenuState::MainMenuState(STATE::Context& context)
: MENU::MenuState("MainMenu", context, new GUI::THEMES::Default, new EventManager(m_renderer))
, m_appCtx(static_cast<ApplicationContext&> (context))
, m_renderer(m_appCtx.getShaderManager(), m_appCtx.getFontManager())
, m_sprite(0)
{
    m_renderer.setScreenDimensions(context.GetWindowWidth(), context.GetWindowHeight());
    // set window dimensions
    getGUI().setDimensions(context.GetWindowWidth(), context.GetWindowHeight());

    // build up GUI
    GUI::COMPONENTS::Button * button;

    button = new GUI::COMPONENTS::Button(m_appCtx.getLocalisation().getText("STR_NEWGAME"));
    getGUI().addComponent(button, *this);
    make_connection(button, click, MainMenuState::NewGameClicked);

    button = new GUI::COMPONENTS::Button(m_appCtx.getLocalisation().getText("STR_OPTIONS"));
    getGUI().addComponent(button, *this);
    make_connection(button, click, MainMenuState::OptionsClicked);

    button = new GUI::COMPONENTS::Button(m_appCtx.getLocalisation().getText("STR_EXIT"));
    getGUI().addComponent(button, *this);
    make_connection(button, click, MainMenuState::ExitClicked);

    getGUI().setLayout(new GUI::LAYOUT::Vertical);
}

MainMenuState::~MainMenuState() {
}

void MainMenuState::NewGameClicked() {
    m_appCtx.getFontManager().showInfo();

}

void MainMenuState::OptionsClicked() {
    L(normal) << "OptionsClicked";
    int active = static_cast<SND::OpenAL::OpenALSoundManager&> (m_appCtx.getSoundManager()).getActiveSources();
    L(normal) << "active sources: " << active;
    (*m_soundInstance)->play();
    active = static_cast<SND::OpenAL::OpenALSoundManager&> (m_appCtx.getSoundManager()).getActiveSources();
    L(normal) << "active sources: " << active;
}

void MainMenuState::ExitClicked() {
    L(normal) << "ExitClicked";
    m_appCtx.getStateManager().scheduleShutdown();
}

void MainMenuState::OnEnter() {
    MENU::MenuState::OnEnter();
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClearStencil(0x0);
    glEnable(GL_STENCIL_TEST);

    // wait for resources to be loaded
    m_appCtx.getFileServer().waitForLoadingFinished();
    
    SYS::Handle<REND::Texture> imageHandle = m_appCtx.getTextureManager().getResourceHandle("image");
    const REND::ShaderProgram* textureDebugShader = m_appCtx.getShaderManager().getShaderProgram("TextureDebug");
    m_sprite = new GL::GLSprite(imageHandle, textureDebugShader);

    // get handles
    m_soundInstance = new SYS::Handle<SND::SoundInstance>(m_appCtx.getSoundManager().getSoundInstance("ping"));
    m_streamInstance = new SYS::Handle<SND::SoundInstance>(m_appCtx.getSoundManager().getSoundInstance("Pamgaea"));

    (*m_streamInstance)->play();
}

void MainMenuState::OnLeave() {
    
    if(m_sprite)
        delete m_sprite;
    
    m_appCtx.getSoundManager().showInfo();
    if (m_soundInstance)
        delete m_soundInstance;
    if (m_streamInstance)
        delete m_streamInstance;
    m_appCtx.getSoundManager().unloadUnusedResources();
    m_appCtx.getSoundManager().showInfo();
}

void MainMenuState::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    /* Enable stencil operations */
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    if(m_sprite)
        m_sprite->draw(this->getRenderer());
    MENU::MenuState::Render();
}

STATE::State* MainMenuState::create(STATE::Context& context) {
    return new MainMenuState(context);
}

void MainMenuState::OnResize(int width, int height) {
    m_renderer.setScreenDimensions(width, height); // update ProjectionMatrix
    getGUI().setDimensions(width, height); // update Layout
    getGUI().invalidate();
}
