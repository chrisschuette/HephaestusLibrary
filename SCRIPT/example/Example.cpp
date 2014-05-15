/* 
 * File:   Example.cpp
 * Author: chris
 * 
 * Created on September 2, 2013, 11:21 AM
 */

#include "Example.h"
#include <iostream>

Example::Example() : SCRIPT::ExportToLua<Example>() {
}

Example::~Example() {
}

int Example::exportToLua() {
    std::cout << "int Example::exportToLua()" << std::endl;
    return -2;
}


