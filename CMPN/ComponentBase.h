/* 
 * File:   ComponentBase.h
 * Author: chris
 *
 * Created on August 30, 2013, 12:50 AM
 */

#ifndef COMPONENTBASE_H
#define	COMPONENTBASE_H

#include "ComponentID.h"
#include "MessageResult.h"

namespace CMPN {
    class MessageBase;
    class ComponentBase {
    public:
        ComponentBase(const ComponentID& cid) : m_CID(cid) {
        }
        const ComponentID& getComponentID() { return m_CID; }
        virtual MessageResult handleMessage(const MessageBase& msg) = 0;
    protected:
        ComponentID m_CID;
    };
}
#endif	/* COMPONENTBASE_H */

