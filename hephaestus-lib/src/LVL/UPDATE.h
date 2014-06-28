/* 
 * File:   UPDATE.h
 * Author: chris
 *
 * Created on May 21, 2014, 1:07 PM
 */

#ifndef LVLUPDATE_H
#define	LVLUPDATE_H

#include "../CMPN/Message.h"
#include "DEFAULT_MIDs.h"
#include "Layer.h"

#include <iostream>

namespace LVL {
    class Context;
    class Level;
    class UPDATE: public CMPN::Message<MID_UPDATE> {
    public:
        UPDATE(unsigned long int t, unsigned long int d, LVL::Level& l) : CMPN::Message<MID_UPDATE>(), time(t), diff(d), level(l) {}
        virtual ~UPDATE() {}
        unsigned long int time;
        unsigned long int diff;
        LVL::Level& level;
    };
}
#endif	/* LVLUPDATE_H */

