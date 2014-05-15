/* 
 * File:   ITest.h
 * Author: chris
 *
 * Created on August 30, 2013, 12:36 AM
 */

#ifndef ITEST_H
#define	ITEST_H

#include "MIDs.h"

struct ITest {
    virtual void test() = 0;
    static const int subscriptions = subscribe(MID_UPDATE)
                                    +subscribe(MID_RENDER);
};
#endif	/* ITEST_H */

