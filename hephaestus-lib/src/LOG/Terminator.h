/* 
 * File:   Terminator.h
 * Author: chris
 *
 * Created on June 16, 2013, 9:49 PM
 */

#ifndef TERMINATOR_H
#define	TERMINATOR_H

#include <ostream>

namespace LOG {
class Terminator {
public:
    Terminator();
    virtual ~Terminator();
private:

};
std::ostream& operator<<(std::ostream& stream, const Terminator& arg);
}
#endif	/* TERMINATOR_H */

