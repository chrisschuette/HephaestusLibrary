/* 
 * File:   Context.h
 * Author: chris
 *
 * Created on June 13, 2013, 5:32 PM
 */

#ifndef STATE_CONTEXT_H
#define	STATE_CONTEXT_H

namespace STATE {

    class Context {
    public:

        Context() {
        }

        virtual ~Context() {
        }
 //       virtual int GetWindowDepth() const = 0;
        virtual int GetWindowHeight() const = 0;
        virtual int GetWindowWidth() const = 0;
    };
}

#endif	/* STATE_CONTEXT_H */

