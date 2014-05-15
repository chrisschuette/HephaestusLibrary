/* 
 * File:   Application.h
 * Author: chris
 *
 * Created on June 13, 2013, 3:17 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include "GL/GLApp.h"
#include "STATE/StateManager.h"
#include "STATE/Context.h"
#include "ResourceManager.h"
#include "BNDL/DirectoryBundle.h"
#include "INPUT/SFML/SFMLInputFactory.h"
#include "INPUT/InputManager.h"
#include "GL/GLShaderManager.h"
#include "GL/FONTS/GLFontManager.h"
#include "ApplicationContext.h"
#include "LOC/LangDict.h"

#include "SND/OpenAL/OpenALSoundManager.h"
#include "REND/TextureManager.h"
#include "GL/GLTextureLoaderFactory.h"

namespace STATE {
    class StateManager;
}

class Application : public GL::GLApp, public ApplicationContext {
public:
    Application();
    virtual void Init();
    virtual void Exec();
    virtual bool IsDone();
    virtual void Shutdown();
    virtual ~Application();

    // Context interface
//    virtual int GetWindowDepth() const;
    virtual int GetWindowHeight() const;
    virtual int GetWindowWidth() const;
    
    virtual ResourceManager& getResourceManager() {
        return m_ResourceManager;
    }
    
    virtual REND::ShaderManager& getShaderManager() {
        return m_shaderManager;
    }
    
    virtual REND::FONTS::FontManager& getFontManager() {
        return m_fontManager;
    }
    
    virtual LOC::LangDict& getLocalisation() {
        return m_localisation;
    }
    
    virtual SND::SoundManager& getSoundManager() {
        return m_soundManager;
    }
    
    virtual FSVR::FileServer& getFileServer()  {
        return m_ResourceManager.getFileServer();
    }

    virtual STATE::StateManager& getStateManager() {
        return m_StateManager;
    }
    
    virtual REND::TextureManager& getTextureManager() {
        return m_textureManager;
    }



private:
    
    // callback functions for events
    static void cursorPositionCallback(GLFWwindow * m_pWindow, double x, double y);
    static void mouseButtonCallback(GLFWwindow * m_pWindow, int button, int action, int mods);
    static void windowResizeCallback(GLFWwindow * m_pWindow, int x, int y);
    static void windowCloseCallback(GLFWwindow *  m_pWindow);
    
    STATE::StateManager& m_StateManager;
    ResourceManager m_ResourceManager;
    BNDL::DirectoryBundle m_DirectoryBundle;
    INPUT::SFML::SFMLInputFactory m_inputFactory;
    const INPUT::InputManager& m_inputManager;
    GL::GLShaderManager m_shaderManager;
    GL::FONTS::GLFontManager m_fontManager;
    LOC::LangDict m_localisation;
    
    // sound -- openal
    SND::OpenAL::OpenALSoundManager m_soundManager;
    GL::GLTextureLoaderFactory m_textureLoaderFactory;
    
    // textures
    REND::TextureManager m_textureManager;
    
};

#endif	/* APPLICATION_H */

