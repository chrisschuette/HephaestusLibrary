/* 
 * File:   ADD_ENTITY.h
 * Author: chris
 *
 * Created on June 4, 2014, 8:58 PM
 */

#ifndef LVLADD_ENTITY_H
#define	LVLADD_ENTITY_H

#include "../CMPN/Message.h"
#include "DEFAULT_MIDs.h"
#include "Entity.h"

namespace LVL {

    class ADD_ENTITY : public CMPN::Message<MID_ADD_ENTITY> {
    public:
        ADD_ENTITY(LVL::Entity* e) : CMPN::Message<MID_ADD_ENTITY>(), entity(e) {}
        virtual ~ADD_ENTITY() {}
        LVL::Entity* entity;
        
    };
}

#endif	/* LVLADD_ENTITY_H */

