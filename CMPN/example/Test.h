/* 
 * File:   Test.h
 * Author: chris
 *
 * Created on August 30, 2013, 12:37 AM
 */

#ifndef TEST_H
#define	TEST_H

#include "../Component.h"
#include "ITest.h"
#include "../MessageBase.h"

#include <iostream>

class Test: public CMPN::Component<ITest,Test> {
public:
    Test(const CMPN::ComponentID& cid);
    virtual ~Test();
    virtual void test() { std::cout << "Test" << std::endl; }
    virtual CMPN::MessageResult handleMessage(const CMPN::MessageBase& msg) {
        std::cout << "Test:";
        if(!msg.Sender.isValid())
            std::cout << " ALL";
        else
            std::cout << " " << msg.Sender.getIndex();
        std::cout << " ==>";
        if(!msg.Addressee.isValid())
            std::cout << " ALL";
        else
            std::cout << " " << msg.Addressee.getIndex();
        std::cout << " Message received." << std::endl;
        return CMPN::MR_IGNORED;
    }

private:

};

#endif	/* TEST_H */

