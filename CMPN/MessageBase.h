/* 
 * File:   MessageBase.h
 * Author: chris
 *
 * Created on August 31, 2013, 5:44 PM
 */

#ifndef MESSAGEBASE_H
#define	MESSAGEBASE_H

#include "MessageTypeID.h"
#include "ObjectID.h"

namespace CMPN {
    class MessageBase {
    public:
        ObjectID Sender;
        ObjectID Addressee;
        const MessageTypeID m_MID;
    protected:
        MessageBase(MessageTypeID mid) : m_MID(mid) { }
        virtual ~MessageBase() {}
    };
}
#endif	/* MESSAGEBASE_H */

