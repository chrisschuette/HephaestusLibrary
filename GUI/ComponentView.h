/* 
 * File:   ComponentView.h
 * Author: chris
 *
 * Created on February 9, 2014, 5:11 PM
 */

#ifndef COMPONENTVIEW_H
#define	COMPONENTVIEW_H

namespace VIEW {
    class Context;
}

namespace GUI {
    class Component;
    class ComponentView {
    public:
        ComponentView();
        virtual ~ComponentView();
        virtual void render(const Component& component, VIEW::Context& pContext) = 0;
    private:

    };
}
#endif	/* COMPONENTVIEW_H */

