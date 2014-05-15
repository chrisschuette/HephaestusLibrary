/* 
 * File:   Box2DController.h
 * Author: chris
 *
 * Created on June 22, 2013, 11:17 AM
 */

#ifndef BOX2DCONTROLLER_H
#define	BOX2DCONTROLLER_H

#include "../Controller.h"

namespace PHYSICS {
    namespace BOX2D {
      class Box2DController: public Controller {
public:
    Box2DController();
    virtual ~Box2DController();
    virtual void evolve(System& system);

private:
    float m_timeStep;
    unsigned int m_vIterations;
    unsigned int m_pIterations;
};
    }
}
#endif	/* BOX2DCONTROLLER_H */

