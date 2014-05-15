/* 
 * File:   Application.cpp
 * Author: chris
 * 
 * Created on June 13, 2013, 3:17 PM
 */

#include "Application.h"
#include "StateManager.h"
#include "INPUT/Input.h"
#include "STATE/State.h"

#include "INPUT/MouseInput.h"

#define LANGUAGE "DICT_DE"

Application::Application()
: GL::GLApp()
, ApplicationContext()
, m_StateManager(StateManager::getInstance())
, m_inputManager(INPUT::InputManager::getInstance())
, m_localisation(LANGUAGE)
, m_soundManager(m_ResourceManager.getFileServer())
, m_textureManager(m_textureLoaderFactory, m_ResourceManager.getFileServer())
{
}

Application::~Application() {
}

void Application::Init() {
    START_TIMER("TEST");
    GL::GLApp::Init();
    
    glfwSetCursorPosCallback( m_pWindow, &Application::cursorPositionCallback ); 
    glfwSetMouseButtonCallback( m_pWindow, &Application::mouseButtonCallback );	
    glfwSetWindowSizeCallback( 	m_pWindow, &Application::windowResizeCallback );
    glfwSetWindowCloseCallback(m_pWindow, &Application::windowCloseCallback );
    
    m_DirectoryBundle.setDirectory("data/TestBundle");
    m_ResourceManager.attachBundle(m_DirectoryBundle);

    // load localisation dictionary
    m_ResourceManager.getFileServer().foregroundLoad(m_localisation, LOC::LangDict::createLoader());

    m_ResourceManager.startFileServer();

    m_soundManager.loadResource("Pamgaea", FSVR::Resource::ONFIRSTUSE);
    m_soundManager.loadResource("ping", FSVR::Resource::ONFIRSTUSE);

    m_shaderManager.addShaderPairFromFile("flat", "shaders/flat.vp", "shaders/flat.fp");
    m_shaderManager.addShaderPairFromFile("debugFlat", "shaders/debugFlat.vp", "shaders/debugFlat.fp");
    m_shaderManager.addShaderPairFromFile("v2f-t2f-c4f", "shaders/v2f-t2f-c4f.vp", "shaders/v2f-t2f-c4f.fp");
    m_shaderManager.addShaderPairFromFile("TextureDebug", "shaders/textureDebug.vp", "shaders/textureDebug.fp");
    m_shaderManager.addShaderPairFromFile("TextShader", "shaders/textShader.vp", "shaders/textShader.fp");

    m_shaderManager.showInfo();

        
    // test texture management
    
    DMGD::Resource<REND::Texture>* image = m_textureManager.loadResource("image", FSVR::Resource::ONFIRSTUSE);
    
    m_StateManager.SwitchToState("MainMenu", *this);
    
    L(normal) << "Elapsed time: " << STOP_TIMER("TEST") << " ms.";
}

void Application::cursorPositionCallback(GLFWwindow * m_pWindow, double x, double y) {
    INPUT::MouseInput mi;
    mi.setEventType(INPUT::MouseInput::MOVED);
    mi.setPosition(x, y);
    INPUT::InputManager::getInstance().processInput(mi);
}

void Application::mouseButtonCallback(GLFWwindow * m_pWindow, int button, int action, int mods) {
    INPUT::MouseInput mi;
    if(action == 0)
        mi.setEventType(INPUT::MouseInput::BUTTONRELEASED);
    else if(action == 1)
        mi.setEventType(INPUT::MouseInput::BUTTONPRESSED);
    else {
        L_SENDER(error, "Application") << "Unknown event type";
        return;
    }
    mi.setPosition(0, 0);
    INPUT::InputManager::getInstance().processInput(mi);
}

void Application::windowResizeCallback(GLFWwindow * m_pWindow, int x, int y) {
    StateManager::getInstance().getCurrentState().OnResize(x,y);
}

void Application::windowCloseCallback(GLFWwindow *  m_pWindow) {
    StateManager::getInstance().scheduleShutdown();
}

void Application::Exec() {
    L(normal) << "in state: " << m_StateManager.GetCurrentStateName();
    while (!IsDone()) {
        // process events
        GL::GLApp::processEvents();

        // update sound manager
        m_soundManager.update();
        
        // update & render
        m_StateManager.Update(*this);
        m_StateManager.Render(*this);

        // Display window contents on screen
        GL::GLApp::display();
    }
}

bool Application::IsDone() {
    return (glfwWindowShouldClose(m_pWindow) || m_StateManager.IsDone());
}

void Application::Shutdown() {
    GL::GLApp::Shutdown();
}

/*
int Application::GetWindowDepth() const {
    return GL::GLApp::GetWindowDepth();
}
 */
int Application::GetWindowHeight() const {
    return GL::GLApp::GetWindowHeight();

}

int Application::GetWindowWidth() const {
    return GL::GLApp::GetWindowWidth();

}
