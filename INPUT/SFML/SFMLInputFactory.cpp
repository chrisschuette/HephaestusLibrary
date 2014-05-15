/* 
 * File:   SFMLInputFactory.cpp
 * Author: chris
 * 
 * Created on June 22, 2013, 4:08 PM
 */

#include <SFML/Window/Event.hpp>

#include "SFMLInputFactory.h"

#include "../JoystickInput.h"
#include "../MouseInput.h"

#include "../../ERR/ERR.h"

namespace INPUT {
    namespace SFML {

        SFMLInputFactory::SFMLInputFactory() {
        }

        SFMLInputFactory::~SFMLInputFactory() {
        }

        Input* SFMLInputFactory::processJoystickEvent(sf::Event& event) {
            JoystickInput* input = new JoystickInput();
            // broken! TODO: fix!
            /* switch(event.Type) {
                 case sf::Event::EventType::JoystickButtonPressed:
                     input->setEventType(JoystickInput::BUTTONPRESSED);
                     break;
                 case sf::Event::JoyButtonReleased:
                     input->setEventType(JoystickInput::BUTTONRELEASED);
                     break;
                 case sf::Event::JoyMoved:
                     input->setEventType(JoystickInput::MOVED);
                     break;
                 default:
                     THROWS("Unknown joystick event.");
             }*/
            return input;
        }

        Input* SFMLInputFactory::processEvent(sf::Event& event) {
            MouseInput* mi;

            // broken! TODO: fix!
            switch (event.type) {
                case sf::Event::MouseMoved:
                    mi = new MouseInput;
                    mi->setEventType(MouseInput::MOVED);
                    mi->setPosition(event.mouseMove.x, event.mouseMove.y);
                    return mi;
                    break;
                case sf::Event::MouseButtonReleased:
                    mi = new MouseInput;
                    mi->setEventType(MouseInput::BUTTONRELEASED);
                    mi->setPosition(0,0);
                    return mi;
                    break;
                case sf::Event::MouseButtonPressed:
                    mi = new MouseInput;
                    mi->setEventType(MouseInput::BUTTONPRESSED);
                    mi->setPosition(0,0);
                    return mi;
                    break;
                default:
                    return 0;
            }
            /*
            sf::Event::EventType type = event.Type;
            if( (type == sf::Event::JoyButtonPressed)
                || (type == sf::Event::JoyButtonReleased)
                        || (type == sf::Event::JoyMoved) )
                return processJoystickEvent(event);
            
            return 0;*/
        }

    }
}
