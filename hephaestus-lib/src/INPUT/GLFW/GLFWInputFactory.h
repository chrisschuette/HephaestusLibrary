/* 
 * File:   GLFWInputFactory.h
 * Author: chris
 *
 * Created on May 27, 2014, 9:45 AM
 */

#ifndef GLFWINPUTFACTORY_H
#define	GLFWINPUTFACTORY_H

#include "../MouseInput.h"
#include "../JoystickInput.h"
#include "../KeyboardInput.h"

#include <GLFW/glfw3.h>
#include <string>


namespace INPUT {
    namespace GLFW {
        namespace GLFWInputFactory_CONST {
            const int MAX_JOYSTICKS = 4;
        }

        class GLFWInputFactory {
        public:
            GLFWInputFactory();
            virtual ~GLFWInputFactory();
            virtual void init();
            virtual void processEvents();

            static void cursorPositionCallback(GLFWwindow * pWindow, double x, double y);
            static void mouseButtonCallback(GLFWwindow * pWindow, int button, int action, int mods);
            static void keyboardCallback(GLFWwindow * pWindow, int key, int scancode, int action, int mods);
        private:

            struct Joystick_State {

                Joystick_State(std::string joy_name, int nButtons, int nAxes)
                : name(joy_name)
                , buttonState(0)
                , axesState(0) {
                    buttonState = new char[nButtons];
                    axesState = new float[nAxes];
                    for (int i = 0; i < nButtons; i++)
                        buttonState[i] = 0;
                    for (int i = 0; i < nAxes; i++)
                        axesState[i] = 0;
                }
                ~Joystick_State() {
                    if (buttonState)
                        delete [] buttonState;
                    if (axesState)
                        delete [] axesState;
                }
                char* buttonState;
                int noOfButtons;
                float* axesState;
                int noOfAxes;
                std::string name;
            };
            Joystick_State* m_joystickStates[GLFWInputFactory_CONST::MAX_JOYSTICKS];
            static INPUT::MouseInput m_mouseInput;
            static INPUT::KeyboardInput m_keyboardInput;
            INPUT::JoystickInput m_joystickInput[GLFWInputFactory_CONST::MAX_JOYSTICKS];
        };
    }
}
#endif	/* GLFWINPUTFACTORY_H */

