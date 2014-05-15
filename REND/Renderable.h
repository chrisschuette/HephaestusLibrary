/* 
 * File:   Renderable.h
 * Author: chris
 *
 * Created on March 23, 2014, 5:26 PM
 */

#ifndef RENDERABLE_H
#define	RENDERABLE_H

namespace REND {
    class Renderer;
    class Renderable {
    public:
        Renderable();
        virtual ~Renderable();
        
        virtual void draw(const Renderer& renderer) = 0;
    private:

    };
}
#endif	/* RENDERABLE_H */

