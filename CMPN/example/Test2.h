/* 
 * File:   Test2.h
 * Author: chris
 *
 * Created on August 30, 2013, 1:21 AM
 */

#ifndef TEST2_H
#define	TEST2_H

#include "../Component.h"
#include "ITest.h"
#include "../MessageBase.h"
#include "MIDs.h"
#include "TestMessage.h"

#include <iostream>

class Test2 : public CMPN::Component<ITest, Test2> {
public:
    Test2(const CMPN::ComponentID& cid);
    virtual ~Test2();

    virtual void test() {
        std::cout << "Test2" << std::endl;
    }

    virtual CMPN::MessageResult handleMessage(const CMPN::MessageBase& msg) {
        std::cout << "Test2:";
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
        
        if(msg.m_MID == MID_UPDATE) {
            std::cout << "Update message received." << std::endl;
            const TestMessage& testMessage = static_cast<const TestMessage&>(msg);
            testMessage.test();
        }
        return CMPN::MR_IGNORED;
    }
private:

};

#endif	/* TEST2_H */

