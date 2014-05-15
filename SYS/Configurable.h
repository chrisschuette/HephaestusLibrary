/* 
 * File:   Configurable.h
 * Author: chris
 *
 * Created on June 12, 2013, 12:00 AM
 */

#ifndef CONFIGURABLE_H
#define	CONFIGURABLE_H

namespace APP {
    class Configuration;
}

namespace SYS {
class Configurable {
public:
    Configurable() {}
    virtual void configure(const APP::Configuration& config) = 0;
    virtual ~Configurable() {}
private:

};
}
#endif	/* CONFIGURABLE_H */

