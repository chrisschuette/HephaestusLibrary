/* 
 * File:   Input.h
 * Author: chris
 *
 * Created on June 22, 2013, 12:51 PM
 */

#ifndef INPUT_H
#define	INPUT_H

#include "Hash.h"

namespace INPUT {
class Input {
public:
    Input();
    virtual ~Input();
    virtual tID getHandlerID() const = 0;
private:
};
}
#endif	/* INPUT_H */

