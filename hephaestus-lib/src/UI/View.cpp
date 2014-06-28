/* 
 * File:   View.cpp
 * Author: chris
 * 
 * Created on May 23, 2014, 7:17 PM
 */

#include "View.h"
#include "LAYOUT/Layout.h"
#include "Context.h"
#include "ComponentView.h"
#include <algorithm>
#include <assert.h>
#include <iostream>

namespace UI {

    struct ComponentDeleter {

        inline void operator()(Component * c) {
            delete c;
        }
    };

    struct ComponentInitializer {

        ComponentInitializer(Context& context) : m_context(context) {
        }
        Context& m_context;

        virtual void operator()(Component * c) {
            c->init(m_context);
        }
    };

    struct ComponentValidator {

        ComponentValidator(Context& context) : m_context(context) {
        }
        Context& m_context;

        virtual void operator()(Component * c) {
            c->validate(m_context);
        }
    };

    struct ComponentRenderer {

        ComponentRenderer(Context& context) : m_context(context) {
        }
        Context& m_context;

        virtual void operator()(Component * c) {
            c->render(m_context);
        }
    };

    struct ComponentUISetter {

        ComponentUISetter(UI* ui) : m_UI(ui) {
        }
        UI* m_UI;

        virtual void operator()(Component * c) {
            c->setUI(m_UI);
        }
    };

    View::View(std::string name)
    : Component(name)
    , m_layout(0) {
        m_containerOrigin.x = 0;
        m_containerOrigin.y = 0;
        m_containerDimensions.x = getWidth();
        m_containerDimensions.y = getHeight();
    }

    View::~View() {
        std::for_each(m_children.begin(), m_children.end(), ComponentDeleter());
        if (m_layout)
            delete m_layout;
    }

    void View::addComponent(Component* component) {
        assert(component);
        m_children.push_back(component);
        setParent(*component, this);
    }

    void View::render(Context& context) const {
        if (isValid() && isVisible()) {
            REND::Renderer& renderer = context.getRenderer();
            renderer.PushMatrix();
            renderer.Translate(m_position.x + getHPadding(), m_position.y + getVPadding(), 0);
            if (m_componentView)
                m_componentView->render(renderer, *this);
            if (m_layout) {
                renderer.Translate(m_containerOrigin.x, m_containerOrigin.y, 0);
                std::for_each(m_children.begin(), m_children.end(), ComponentRenderer(context));
            }
            renderer.PopMatrix();
        }
    }

    void View::validate(Context& context) {
        if (!isValid()) {
            Component::validate(context);
            std::for_each(m_children.begin(), m_children.end(), ComponentInitializer(context));
            if ((m_layout != 0) && hasChildren())
                m_layout->layout(*this, context);
            std::for_each(m_children.begin(), m_children.end(), ComponentValidator(context));
        }
    }

    void View::resize(int x, int y) {
        m_dimensions.x = x;
        m_dimensions.y = y;
        if (m_componentView)
            m_componentView->update(*this);
        m_valid = false;
    }

    void View::setUI(UI* ui) {
        Component::setUI(ui);
        std::for_each(m_children.begin(), m_children.end(), ComponentUISetter(ui));
    }

    Component* View::getComponent(const MATH::ivec2& position) {
        // if it is not within the current view it is definitely
        // not in any of the children
        if (!isInRect(position))
            return 0;

        MATH::ivec2 relative;
        relative.x = position.x - m_position.x - getHPadding() - getContainerHOrigin();
        relative.y = position.y - m_position.y - getVPadding() - getContainerVOrigin();

        for (tViewList::iterator i = m_children.begin(), e = m_children.end();
                i != e; ++i)
            if ((*i)->isInRect(relative))
                return (*i)->getComponent(relative);
        return this;
    }

}
