/* 
 * File:   BodyUserData.h
 * Author: chris
 *
 * Created on June 3, 2014, 2:40 PM
 */

#ifndef CUSTOMBODYUSERDATA_H
#define	CUSTOMBODYUSERDATA_H

#include "../CMPN/ObjectID.h"
#include "../PHYSICS/BodyUserData.h"


namespace LVL {
    class BodyUserData: public PHYSICS::BodyUserData {
    public:
        BodyUserData(CMPN::ObjectID objectID)
        : PHYSICS::BodyUserData()
        , m_objectID(objectID) {}
        virtual ~BodyUserData() {}
        const CMPN::ObjectID& getObjectID() const { return m_objectID; }
    private:
        CMPN::ObjectID m_objectID;
    };
}
#endif	/* CUSTOMBODYUSERDATA_H */

