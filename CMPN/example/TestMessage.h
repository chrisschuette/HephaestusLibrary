/* 
 * File:   TestMessage.h
 * Author: chris
 *
 * Created on August 31, 2013, 5:47 PM
 */

#ifndef TESTMESSAGE_H
#define	TESTMESSAGE_H

#include "../Message.h"
#include "MIDs.h"

#include <iostream>

class TestMessage: public CMPN::Message<MID_UPDATE> {
public:
    TestMessage();
    virtual ~TestMessage();
    void test() const { std::cout << "TestMessage." << std::endl; }
private:

};

#endif	/* TESTMESSAGE_H */

