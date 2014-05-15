/* 
 * File:   Container.h
 * Author: chris
 *
 * Created on February 2, 2014, 6:37 PM
 */

#ifndef CONTAINER_H
#define	CONTAINER_H

#include "../VIEW/View.h"
#include "../GEOMETRY/Rectangle.h"

namespace GUI {
    class Theme;
    class Context;
    namespace LAYOUT {
        class Layout;
    }

    class Container : public VIEW::View, public GEOMETRY::Rectangle<int> {
    public:
        Container();
        virtual ~Container();
        virtual void validate();
        void setLayout(LAYOUT::Layout* layout);
        virtual void initView(Theme* theme, Context& ctx);
        virtual void render(VIEW::Context& pContext) const;
    private:
        LAYOUT::Layout* m_pLayout;
    };
}

#endif	/* CONTAINER_H */

