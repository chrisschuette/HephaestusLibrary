/* 
 * File:   BodyDescription.h
 * Author: chris
 *
 * Created on May 21, 2014, 10:27 PM
 */

#ifndef BODYDESCRIPTION_H
#define	BODYDESCRIPTION_H

#include "../MATH/vec234.h"

namespace PHYSICS {
    class BodyDescription {
    public:
        enum BODY_TYPE {STATIC, KINEMATIC, DYNAMIC};
    public:
        BodyDescription();
        virtual ~BodyDescription();
        
        virtual BodyDescription* clone() const = 0;
        
        // setters
        virtual void setBodyType(BODY_TYPE type) = 0;
        virtual void setPosition(float x, float y) = 0;
        virtual void setAngle(float angle) = 0;
    private:

    };
}
#endif	/* BODYDESCRIPTION_H */

