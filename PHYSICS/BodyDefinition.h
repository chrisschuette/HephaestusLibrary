/* 
 * File:   BodyDefinition.h
 * Author: chris
 *
 * Created on June 19, 2013, 1:56 AM
 */

#ifndef BODYDEFINITION_H
#define	BODYDEFINITION_H

#include "type.h"

namespace PHYSICS {
    class Orientation;
    class Position;
class BodyDefinition {
public:
    BodyDefinition();
    virtual ~BodyDefinition();
    
    virtual void setOrientation(const Orientation& orientation) = 0;
    virtual void setPosition(const Position& position) = 0;
    
    virtual void setBodyType(BODY_TYPE type) = 0;
private:
};
}
#endif	/* BODYDEFINITION_H */

