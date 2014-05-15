/* 
 * File:   Test.cpp
 * Author: chris
 * 
 * Created on August 30, 2013, 12:37 AM
 */

#include "Test.h"

Test::Test(const CMPN::ComponentID& cid) : CMPN::Component<ITest, Test>(cid) {
}

Test::~Test() {
}

