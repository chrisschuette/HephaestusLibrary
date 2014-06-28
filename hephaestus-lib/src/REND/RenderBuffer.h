/* 
 * File:   RenderBuffer.h
 * Author: chris
 *
 * Created on June 1, 2014, 3:09 PM
 */

#ifndef RENDERBUFFER_H
#define	RENDERBUFFER_H

namespace REND {
    class RenderBuffer {
    public:
        RenderBuffer();
        virtual ~RenderBuffer();
        
        virtual void draw() = 0;
    private:

    };
}
#endif	/* RENDERBUFFER_H */

