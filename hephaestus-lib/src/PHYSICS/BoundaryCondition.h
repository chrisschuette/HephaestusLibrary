/* 
 * File:   BoundaryCondition.h
 * Author: chris
 *
 * Created on June 3, 2014, 3:29 PM
 */

#ifndef BOUNDARYCONDITION_H
#define	BOUNDARYCONDITION_H

namespace PHYSICS {
    class System;
    class BoundaryCondition {
    public:
        BoundaryCondition() {}
        virtual ~BoundaryCondition() {}
        
        virtual void apply(System& system) = 0;
        virtual void onResize(float width, float height) = 0;
    private:
    };
}
#endif	/* BOUNDARYCONDITION_H */

