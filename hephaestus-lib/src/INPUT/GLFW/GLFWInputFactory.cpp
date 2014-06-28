/* 
 * File:   GLFWInputFactory.cpp
 * Author: chris
 * 
 * Created on May 27, 2014, 9:45 AM
 */

#include "GLFWInputFactory.h"
#include "../InputManager.h"
#include "../../LOG/Core.h"

#define NAME "GLFWInputFactory"

namespace INPUT {
    namespace GLFW {

        INPUT::MouseInput GLFWInputFactory::m_mouseInput;
        INPUT::KeyboardInput GLFWInputFactory::m_keyboardInput;

        GLFWInputFactory::GLFWInputFactory() {
        }

        GLFWInputFactory::~GLFWInputFactory() {
            for(int j = 0; j < GLFWInputFactory_CONST::MAX_JOYSTICKS; j++)
                if(m_joystickStates[j])
                    delete m_joystickStates[j];
        }

        void GLFWInputFactory::cursorPositionCallback(GLFWwindow * m_pWindow, double x, double y) {
            m_mouseInput.setEventType(INPUT::MouseInput::MOVED);
            m_mouseInput.setPosition(x, y);
            INPUT::InputManager::getInstance().processInput(m_mouseInput);
        }

        void GLFWInputFactory::mouseButtonCallback(GLFWwindow * m_pWindow, int button, int action, int mods) {
            if (action == 0)
                m_mouseInput.setEventType(INPUT::MouseInput::BUTTONRELEASED);
            else if (action == 1)
                m_mouseInput.setEventType(INPUT::MouseInput::BUTTONPRESSED);
            else {
                L_SENDER(error, "Application") << "Unknown event type";
                return;
            }
            m_mouseInput.setPosition(0, 0);
            INPUT::InputManager::getInstance().processInput(m_mouseInput);
        }

        void GLFWInputFactory::keyboardCallback(GLFWwindow * pWindow, int key, int scancode, int action, int mods) {
            switch (action) {
                case GLFW_PRESS:
                    m_keyboardInput.setAction(INPUT::KeyboardInput::KEYDOWN);
                    break;
                case GLFW_RELEASE:
                    m_keyboardInput.setAction(INPUT::KeyboardInput::KEYUP);
                    break;
                case GLFW_REPEAT:
                    m_keyboardInput.setAction(INPUT::KeyboardInput::KEYREPEAT);
                    break;
            }
            m_keyboardInput.setKey(key);
            INPUT::InputManager::getInstance().processInput(m_keyboardInput);
        }

        void GLFWInputFactory::init() {
            for (int j = 0; j < GLFWInputFactory_CONST::MAX_JOYSTICKS; j++) {
                if (GL_TRUE == glfwJoystickPresent(j)) {
                    const char* joy_name = glfwGetJoystickName(j);
                    int nButtons;
                    const unsigned char * buttonState = glfwGetJoystickButtons(j, &nButtons);
                    int nAxes = 0;
                    const float* axesState = glfwGetJoystickAxes(j, &nAxes);
                    m_joystickStates[j] = new Joystick_State(joy_name, nButtons, nAxes);
                    memcpy(m_joystickStates[j]->axesState, axesState, nAxes * sizeof (float));
                    memcpy(m_joystickStates[j]->buttonState, buttonState, nButtons * sizeof (char));
                    L(normal) << "Joystick " << j << ": " << joy_name << " " << nButtons << " buttons, " << nAxes << " axes.";
                    m_joystickInput[j].setAxes(nAxes);
                } else
                    m_joystickStates[j] = 0;
            }
        }

        void GLFWInputFactory::processEvents() {
            glfwPollEvents();

            // check the joystick states
            for (int j = 0; j < GLFWInputFactory_CONST::MAX_JOYSTICKS; j++) {
                if (m_joystickStates[j]) {
                    int nAxes;
                    const float * axesState = glfwGetJoystickAxes(j, &nAxes);
                    int nButtons;
                    const unsigned char * buttonState = glfwGetJoystickButtons(j, &nButtons);

                    // send button updates

                    for (int i = 0; i < nButtons; i++) {
                        if (m_joystickStates[j]->buttonState[i] - buttonState[i] == 1) {// button up
                            m_joystickInput[j].setInputType(INPUT::JoystickInput::BUTTONUP);
                            INPUT::InputManager::getInstance().processInput(m_joystickInput[j]);
                        } else if (m_joystickStates[j]->buttonState[i] - buttonState[i] == -1) {// button down 
                            m_joystickInput[j].setInputType(INPUT::JoystickInput::BUTTONDOWN);
                            INPUT::InputManager::getInstance().processInput(m_joystickInput[j]);
                        }
                    }
                    memcpy(m_joystickStates[j]->buttonState, buttonState, nButtons * sizeof (char));

                    // send axes update
                    m_joystickInput[j].setInputType(INPUT::JoystickInput::AXESUPDATE);
                    m_joystickInput[j].updateAxesValues(axesState);
                    INPUT::InputManager::getInstance().processInput(m_joystickInput[j]);
                }

            }
        }
    }
}