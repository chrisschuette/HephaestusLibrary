/* 
 * File:   System.h
 * Author: chris
 *
 * Created on June 19, 2013, 1:39 AM
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#include "../MEM/Pool.h"
#include "ID.h"
#include "../LOG/Source.h"

namespace MEM {
    template <class T>
    class Pool;
}

namespace SYS {
    template <class T>
    class Reference;
        template <class T>
    class Handle;
}

namespace PHYSICS {
    class BodyDefinition;
    class Body;
    class BodyPart;
class System: public LOG::Source {
public:
    System();
    virtual SYS::Handle<Body> createBody(const BodyDefinition& bodyDef) = 0;
    virtual void attachBodyPart(SYS::Handle<Body>& body, const BodyPart& bodyPart) = 0;
    virtual MEM::Pool< SYS::Reference< Body > >& getReferencePool() = 0;
    virtual SYS::Handle<Body> getBody(tID id) = 0;
    virtual void showBodyInfo() = 0;
    virtual ~System();
private:
};
}

#endif	/* SYSTEM_H */

