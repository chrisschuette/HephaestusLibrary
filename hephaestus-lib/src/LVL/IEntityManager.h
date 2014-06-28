/* 
 * File:   IEntityManager.h
 * Author: chris
 *
 * Created on June 5, 2014, 9:26 AM
 */

#ifndef IENTITYMANAGER_H
#define	IENTITYMANAGER_H

#include "DEFAULT_MIDs.h"
#include "../MATH/vec234.h"

namespace LVL {
    class Level;
    struct IEntityManager {
        IEntityManager() : m_level(0) {}
        virtual void update(unsigned long int time, unsigned long int diff) = 0;
        static const int subscriptions = subscribe(MID_ADD_ENTITY) + subscribe(MID_REMOVE_ENTITY);
        void setLevel(Level* level) { m_level = level; }
    protected:
        Level* m_level;
    };
}

#endif	/* IENTITYMANAGER_H */

