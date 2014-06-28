/* 
 * File:   InputFactory.h
 * Author: chris
 *
 * Created on May 26, 2014, 5:08 PM
 */

#ifndef INPUTFACTORY_H
#define	INPUTFACTORY_H

namespace INPUT {
class InputFactory {
public:
    InputFactory();
    virtual ~InputFactory();
    
    virtual void init() = 0;
    virtual void processEvents() = 0;
private:

};
}
#endif	/* INPUTFACTORY_H */

