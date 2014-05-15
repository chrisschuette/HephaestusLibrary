/* 
 * File:   Container.cpp
 * Author: chris
 * 
 * Created on February 2, 2014, 6:37 PM
 */

#include "Container.h"
#include "LAYOUT/Layout.h"
#include "Context.h"
#include "Renderer.h"
#include "Component.h"
#include <iostream>

namespace GUI {
    
    struct ComponentViewInitializer : public VIEW::ViewVisitor {
        ComponentViewInitializer(Theme* theme, Context& ctx) : m_theme(theme), m_ctx(ctx) {}
        virtual void operator()(VIEW::Element * pComponent) {
            Component* c = static_cast<Component* >(pComponent);
            c->initView(m_theme, m_ctx);
        }
        Theme* m_theme;
        Context& m_ctx;
    };

    Container::Container()
    : VIEW::View()
    , GEOMETRY::Rectangle<int>()
    , m_pLayout(0) {
        m_position.x = 0;
        m_position.y = 0;
        m_dimension.x = 0;
        m_dimension.y = 0;
    }

    Container::~Container() {
        if (m_pLayout)
            delete m_pLayout;
    }

    void Container::setLayout(LAYOUT::Layout* layout) {
        if (m_pLayout)
            delete m_pLayout;
        m_pLayout = layout;
    }

    void Container::validate() {
        if (!isValid()) {
            // check if we have a layoutmanager and children
            // if so, do a layout call.
            if ((m_pLayout != 0) && hasChildren()) {
                m_pLayout->layoutContainer(*this);
            }
            VIEW::View::validate();
        }
    }
    
    void Container::initView(Theme* theme, Context& ctx) {
        std::for_each(m_children.begin(), m_children.end(), ComponentViewInitializer(theme, ctx));
    }


    void Container::render(VIEW::Context& context) const {
        if(isValid() && isVisible()) {
            Context& ctx = static_cast<Context&>(context);
            
            GUI::Renderer& renderer = ctx.getRenderer();
            renderer.PushMatrix();
            renderer.Translate(m_position.x, m_position.y);

            // draw children
            VIEW::View::renderChildren(context);
        
            renderer.PopMatrix();

        }
    }

}