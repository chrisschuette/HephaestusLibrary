/* 
 * File:   Controller.h
 * Author: chris
 *
 * Created on June 22, 2013, 11:15 AM
 */

#ifndef CONTROLLER_H
#define	CONTROLLER_H

namespace PHYSICS {
    class System;
    class Controller {
public:
    Controller();
    virtual ~Controller();
    virtual void evolve(System& system) = 0;
private:

};
}
#endif	/* CONTROLLER_H */

