/* 
 * File:   Component.cpp
 * Author: chris
 * 
 * Created on May 23, 2014, 7:16 PM
 */

#include "Component.h"
#include "ComponentView.h"
#include "Context.h"
#include "../UTIL/hash.h"
#include "UI.h"

namespace UI {

    Component::Component(std::string name)
    : EVENT::EventResponder()
    , m_typeID(UTIL::hash(name))
    , m_parent(0)
    , m_componentView(0)
    , m_valid(false)
    , m_visible(true)
    , m_UI(0) {
        m_position.x = 0;
        m_position.y = 0;
        m_dimensions.x = 0;
        m_dimensions.y = 0;
        m_minDimensions.x = 0;
        m_minDimensions.y = 0;
        m_maxDimensions.x = -1;
        m_maxDimensions.y = -1;
        m_heightBehaviour = COMPACT;
        m_widthBehaviour = COMPACT;
        m_padding.x = 0;
        m_padding.y = 0;
    }

    Component::~Component() {
        if (m_componentView)
            delete m_componentView;
    }

    void Component::init(Context& context, bool force) {
        if (force && m_componentView) {
            delete m_componentView;
            m_componentView = 0;
        }
        if (m_UI && m_UI->getTheme() && !m_componentView)
            m_componentView = m_UI->getTheme()->createComponentView(*this, context);
    }

    void Component::setParent(Component& component, Component* parent) {
        component.m_parent = parent;
    }

    void Component::validate(Context& context) {
        m_valid = true;
        /*if (m_UI && m_UI->getTheme()) {
            init(context);
            m_valid = true;
        } else
            invalidate();*/
        
    }

    void Component::invalidate() {
        m_valid = false;
        if (m_parent != 0)
            m_parent->invalidate();
    }

    void Component::render(Context& context) const {
        if (m_componentView && isValid() && isVisible()) {
            REND::Renderer& renderer = context.getRenderer();
            renderer.PushMatrix();
            renderer.Translate(m_position.x + getHPadding(), m_position.y + getVPadding(), 0);
            // draw the ComponentView
            if (m_componentView)
                m_componentView->render(renderer, *this);
            renderer.PopMatrix();
        }
    }

    void Component::setMinimumSize(int x, int y) {
        m_minDimensions.x = x;
        m_minDimensions.y = y;
    }

    void Component::setMaximumSize(int x, int y) {
        m_maxDimensions.x = x;
        m_maxDimensions.y = y;
    }

    void Component::resize(int x, int y) {
        m_dimensions.x = x;
        m_dimensions.y = y;
        if (m_componentView)
            m_componentView->update(*this);
    }

    void Component::setSizeBehaviour(SIZE_BEHAVIOUR x, SIZE_BEHAVIOUR y) {
        m_heightBehaviour = y;
        m_widthBehaviour = x;
    }

    bool Component::isInRect(const MATH::ivec2& point) const {
        MATH::ivec2 relative;
        relative.x = point.x - m_position.x - getHPadding();
        relative.y = point.y - m_position.y - getHPadding();
        if ((relative.x >= 0) &&
                (relative.x <= (m_dimensions.x - 2 * getHPadding())) &&
                (relative.y >= 0) &&
                (relative.y <= (m_dimensions.y - 2 * getHPadding())))
            return true;
        return false;

    }

    Component* Component::getComponent(const MATH::ivec2& position) {
        if (isInRect(position))
            return this;
        return 0;
    }

    void Component::becomeFirstResponder() {
        m_UI->getEventManager().setFirstResponder(this);
    }

}
