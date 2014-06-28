/* 
 * File:   ComponentBase.h
 * Author: chris
 *
 * Created on August 30, 2013, 12:50 AM
 */

#ifndef COMPONENTBASE_H
#define	COMPONENTBASE_H

#include "ComponentID.h"
#include "ObjectID.h"
#include "MessageResult.h"

#include <iostream>

namespace CMPN {
    class MessageBase;
    class Context;
    class ComponentBase {
    public:
        ComponentBase(const ComponentID& cid, const ObjectID& oid)
        : m_CID(cid)
        , m_OID(oid)
        {
        }
        const ComponentID& getComponentID() { return m_CID; }
        virtual MessageResult handleMessage(const MessageBase& msg) {
            return CMPN::MR_IGNORED;
        }
        
        virtual void init(Context& ctx) { }
        const ObjectID& getObjectID() { return m_OID; }
    protected:
        ComponentID m_CID;
        ObjectID m_OID;
    };
}
#endif	/* COMPONENTBASE_H */

