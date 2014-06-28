/*
 * File:   GLApp.cpp
 * Author: chris
 *
 * Created on June 12, 2013, 8:49 PM
 */
#include "GLApp.h"
#include "../APP/Configuration.h"
#include "../ERR/ERR.h"
#include "../APP/FPSController.h"
#include "../LOG/Core.h"

#define NAME "GLApp"

namespace GL {

    void error_callback(int error, const char* description) {
        L(critical) << description;
    }

    GLApp::GLApp()
    : APP::Application()
    , m_width(0)
    , m_height(0)
    , m_depth(0)
    , m_pWindow(0)
    , m_FPSController(0) {
        m_pConfiguration->AddCompulsory("application.window.title");
        m_pConfiguration->AddCompulsory("application.window.size.width");
        m_pConfiguration->AddCompulsory("application.window.size.height");
        m_pConfiguration->AddCompulsory("application.window.size.depth");

        // initialise window library
        if (!glfwInit())
            THROWS("Unable to initialize GLFW.");

    }

    GLApp::~GLApp() {
        glfwTerminate();
    }

    GLFWwindow* GLApp::GetWindow() const {
        return m_pWindow;
    }

    std::string GLApp::GetTitle() const {
        return m_title;
    }

    /*
    int GLApp::GetWindowDepth() const {

    }
     */
    int GLApp::GetWindowHeight() const {
        int width, height;
        glfwGetFramebufferSize(m_pWindow, &width, &height);
        return height;
    }

    int GLApp::GetWindowWidth() const {
        int width, height;
        glfwGetFramebufferSize(m_pWindow, &width, &height);
        return width;
    }

    MATH::ivec2 GLApp::GetWindowDimensions() const {
        MATH::ivec2 dimensions;
        glfwGetFramebufferSize(m_pWindow, &dimensions.x, &dimensions.y);
        return dimensions;
    }

    void GLApp::display() {
        if (m_FPSController)
            m_FPSController->limitFPS();
        glfwSwapBuffers(m_pWindow);
    }

    void GLApp::initGLEW() {
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();

        if (GLEW_OK != err) {
            /* Problem: glewInit failed, something is seriously wrong. */
            // fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

        }

        L(normal) << "Status: Using GLEW " << (const char*) glewGetString(GLEW_VERSION);

    }

    void GLApp::Init() {
        // configure logging
        //LOG::Logging::getInstance().configure(*m_pConfiguration);
        m_pConfiguration->Get("application.window.title", m_title);
        m_pConfiguration->Get("application.window.size.width", m_width);
        m_pConfiguration->Get("application.window.size.height", m_height);
        m_pConfiguration->Get("application.window.size.depth", m_depth);

        int FPS;
        if (m_pConfiguration->Get("application.window.FPS", FPS)) {
            m_FPSController = new APP::FPSController(APP::Clock::getInstance(), FPS);
            L(normal) << "Limiting FPS to " << FPS;
        }

        glfwWindowHint(GLFW_SAMPLES, 8);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwSetErrorCallback(error_callback);
        //glEnable(GL_MULTISAMPLE); 

        /*
        sf::ContextSettings settings;
        settings.stencilBits = 8;
        settings.depthBits = 24;
        settings.antialiasingLevel = 0;
        settings.minorVersion = 3;
        settings.majorVersion = 3;


        m_pWindow = new sf::Window(sf::VideoMode(m_width, m_height, m_depth), m_title,  sf::Style::Default, settings);*/
        m_pWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
        if (!m_pWindow)
            THROWS("Unable to create window.");
        /* Make the window's context current */
        glfwMakeContextCurrent(m_pWindow);
        initGLEW();

        glEnable(GL_TEXTURE_2D);
        int maxtexsize;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxtexsize);
        L(normal) << "max. texture size: " << maxtexsize;
    }

    void GLApp::Shutdown() {
        // no shutdown code needed
        glfwDestroyWindow(m_pWindow);

        if (m_FPSController)
            delete m_FPSController;

    }
}
