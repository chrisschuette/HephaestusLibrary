/* 
 * File:   SFMLInputFactory.h
 * Author: chris
 *
 * Created on June 22, 2013, 4:08 PM
 */

#ifndef SFMLInputFactory_H
#define	SFMLInputFactory_H

#include "../InputFactory.h"

#include <SFML/Window/Event.hpp>

namespace INPUT {
    class Input;
    namespace SFML {
class SFMLInputFactory: public INPUT::InputFactory {
public:
    SFMLInputFactory();
    virtual void init();
    
    Input* processEvent(sf::Event& event);
    virtual ~SFMLInputFactory();
private:
    Input* processJoystickEvent(sf::Event& event);

};
    }
}
#endif	/* SFMLInputFactory_H */

