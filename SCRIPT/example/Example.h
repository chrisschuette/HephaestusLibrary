/* 
 * File:   Example.h
 * Author: chris
 *
 * Created on September 2, 2013, 11:21 AM
 */

#ifndef EXAMPLE_H
#define	EXAMPLE_H

#include "../ExportToLua.h"

class Example: public SCRIPT::ExportToLua<Example> {
public:
    Example();
    virtual ~Example();
    static int exportToLua();
private:
};

#endif	/* EXAMPLE_H */

