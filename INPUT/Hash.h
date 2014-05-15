/* 
 * File:   Hash.h
 * Author: chris
 *
 * Created on June 22, 2013, 3:35 PM
 */

#ifndef HASH_H
#define	HASH_H

#include <typeinfo>
#include "id.h"

#define HANDLERID(t) INPUT::hash(typeid(t).name())
#define HANDLERIDFUNCTIONS public:\
    virtual tID getHandlerID() const { return m_handlerID; }\
private:\
    static tID m_handlerID;

namespace INPUT {
        tID hash(const char * identifier);

}

#endif	/* HASH_H */

