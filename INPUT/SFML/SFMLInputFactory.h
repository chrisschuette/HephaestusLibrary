/* 
 * File:   SFMLInputFactory.h
 * Author: chris
 *
 * Created on June 22, 2013, 4:08 PM
 */

#ifndef SFMLInputFactory_H
#define	SFMLInputFactory_H

#include <SFML/Window/Event.hpp>

namespace INPUT {
    class Input;
    namespace SFML {
class SFMLInputFactory {
public:
    SFMLInputFactory();
    Input* processEvent(sf::Event& event);
    virtual ~SFMLInputFactory();
private:
    Input* processJoystickEvent(sf::Event& event);

};
    }
}
#endif	/* SFMLInputFactory_H */

