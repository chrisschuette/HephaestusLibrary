/* 
 * File:   ComponentView.h
 * Author: chris
 *
 * Created on May 23, 2014, 7:36 PM
 */

#ifndef COMPONENTVIEW_H
#define	COMPONENTVIEW_H

namespace REND {
        class Renderer;
}

namespace UI {
    class Component;
    class ComponentView {
    public:
        ComponentView();
        virtual ~ComponentView();
        virtual void update(Component& component) = 0;
        
        virtual void render(REND::Renderer& renderer, const Component& component) = 0;
    private:

    };
}
#endif	/* COMPONENTVIEW_H */

