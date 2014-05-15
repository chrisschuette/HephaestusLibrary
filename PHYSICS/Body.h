/* 
 * File:   Body.h
 * Author: chris
 *
 * Created on June 19, 2013, 1:45 AM
 */

#ifndef BODY_H
#define	BODY_H

#include "../SYS/IsReferenceCounted.h"
#include "ID.h"
#include <list>

namespace PHYSICS {
    class System;
    class BodyDefinition;
    class BodyPart;
    class Body: public SYS::IsReferenceCounted< Body > {
        friend class SYS::IsReferenceCounted< Body >;
    public:
        tID getID() const { return m_ID; }
        virtual int getBodyType() const = 0;
protected:
    Body(tID ID,/* const BodyDefinition& definition,*/ System& system);
    virtual ~Body();
protected:
    System& m_system;
    tID m_ID;
//    std::list<BodyPart*> m_bodyParts;
    friend class System;
    private:
        Body(const Body& orig);

    };
    typedef SYS::Handle<Body> BodyHandle;

}

#endif	/* BODY_H */

