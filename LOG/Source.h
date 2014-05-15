/* 
 * File:   Source.h
 * Author: chris
 *
 * Created on June 12, 2013, 8:05 PM
 */

#ifndef SOURCE_H
#define	SOURCE_H

#include "Core.h"

#include <string>

//#define DEBUG


namespace LOG {
class Source {
public:
    Source(std::string channel);
#ifdef DEBUG
    const std::string getName() const { return m_name; }
#else
    const std::string getName() const { return ""; }
#endif
    virtual ~Source();
protected:
#ifdef DEBUG
    std::string m_name;
#endif
};
}
#endif	/* SOURCE_H */

