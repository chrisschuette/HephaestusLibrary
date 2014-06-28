/* 
 * File:   REMOVE_ENTITY.h
 * Author: chris
 *
 * Created on June 4, 2014, 9:01 PM
 */

#ifndef REMOVE_ENTITY_H
#define	REMOVE_ENTITY_H

#include "../CMPN/Message.h"
#include "DEFAULT_MIDs.h"
#include "../CMPN/ObjectID.h"

namespace LVL {

    class REMOVE_ENTITY : public CMPN::Message<MID_REMOVE_ENTITY> {
    public:
        REMOVE_ENTITY( const CMPN::ObjectID& object )
        : CMPN::Message<MID_REMOVE_ENTITY>()
        , objectID(object)
        {}
        virtual ~REMOVE_ENTITY() {}
        CMPN::ObjectID objectID;
    };
}

#endif	/* REMOVE_ENTITY_H */

