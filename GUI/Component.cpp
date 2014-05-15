/* 
 * File:   Component.cpp
 * Author: chris
 * 
 * Created on February 2, 2014, 6:35 PM
 */

#include "Component.h"
#include "ComponentView.h"
#include "Context.h"
#include "Renderer.h"
#include "Theme.h"

namespace GUI {

    Component::Component(TypeID typeID)
    : VIEW::Element()
    , EVENT::EventListener()
    , GEOMETRY::Rectangle<int>()
    , m_componentView(0)
    , m_typeID(typeID) {
        m_position.x = 0;
        m_position.y = 0;
        m_dimension.x = 0;
        m_dimension.y = 0;
    }

    Component::~Component() {
        if (m_componentView)
            delete m_componentView;
    }

    void Component::initView(Theme* theme, Context& ctx) {
        if (m_componentView)
            delete m_componentView;
        if (theme)
            m_componentView = theme->getComponentView(m_typeID, *this, ctx);
    }

    void Component::render(VIEW::Context& context) const {
        Context& ctx = static_cast<Context&> (context);

        if (m_componentView && isValid() && isVisible()) {
            GUI::Renderer& renderer = ctx.getRenderer();
            renderer.PushMatrix();
            renderer.Translate(m_position.x, m_position.y);
            // draw the ComponentView
            m_componentView->render(*this,context);
            renderer.PopMatrix();
        }
    }

}
