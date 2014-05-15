/* 
 * File:   Component.h
 * Author: chris
 *
 * Created on February 2, 2014, 6:35 PM
 */

#ifndef GUI_COMPONENT_H
#define	GUI_COMPONENT_H

#include "../VIEW/Element.h"
#include "EVENT/EventListener.h"
#include "../GEOMETRY/Rectangle.h"
#include "TypeID.h"

namespace GUI {
    class Theme;
    class Context;
    class ComponentView;
    class Component: public VIEW::Element, public EVENT::EventListener, public GEOMETRY::Rectangle<int> {
    public:
        Component(TypeID typeID);
        virtual ~Component();
        virtual void render(VIEW::Context& pContext) const;
        virtual void initView(Theme* theme, Context& ctx);
        virtual int getWidth() { return m_dimension.x; }
        virtual int getHeight() { return m_dimension.y; }
        virtual void setWidth(int w) { m_dimension.x = w; }
        virtual void setHeight(int  h) { m_dimension.y = h; }
    private:
        ComponentView* m_componentView;
        TypeID m_typeID;
    };
}
#endif	/* GUI_COMPONENT_H */

