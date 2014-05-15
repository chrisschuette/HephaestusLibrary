/* 
 * File:   Message.h
 * Author: chris
 *
 * Created on August 30, 2013, 2:26 AM
 */

#ifndef MESSAGE_H
#define	MESSAGE_H

#include "MessageBase.h"
#include "MessageTypeID.h"

namespace CMPN {
    template <int MID>
    class Message : public MessageBase {
    public:
        Message() : MessageBase(MID) {
        }
        virtual ~Message() {
        }
    private:
    };
}

#endif	/* MESSAGE_H */

