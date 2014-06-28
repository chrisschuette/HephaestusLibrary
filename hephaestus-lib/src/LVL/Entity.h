/* 
 * File:   Entity.h
 * Author: chris
 *
 * Created on May 21, 2014, 12:27 PM
 */

#ifndef ENTITY_H
#define	ENTITY_H

#include "../CMPN/Container.h"

namespace LVL {
    class Entity: public CMPN::Container {
    public:
        Entity();
        virtual ~Entity();
    private:

    };
}
#endif	/* ENTITY_H */

