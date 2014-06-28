/* 
 * File:   Button.cpp
 * Author: chris
 * 
 * Created on May 23, 2014, 8:35 PM
 */

#include "Button.h"
#include "../ComponentView.h"
#include "../EVENT/MouseClickHandler.h"
#include "../EVENT/MouseClickToFirstResponder.h"
#include "../EVENT/DesaturateBackgroundOnHover.h"
#include <iostream>

namespace UI {
    namespace COMPONENTS {

        Button::Button() : Component("Button"), m_textAlign(CENTER)
        , m_VTextAlign(MIDDLE) {
            m_backgroundColor.r = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.g = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.b = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.a = 1.f;

            m_textColor.r = 0.f;
            m_textColor.g = 0.f;
            m_textColor.b = 0.f;
            m_textColor.a = 1.f;

            setSizeBehaviour(Component::FIXED, Component::FIXED);
            addEventHandler(new EVENT::MouseClickToFirstResponder<Button>(*this));
            addEventHandler(new EVENT::MouseClickHandler<Button>(*this));
            addEventHandler(new EVENT::DesaturateBackgroundOnHover<Button>(*this));
        }

        Button::Button(std::string caption) : Component("Button"), m_textAlign(CENTER)
        , m_VTextAlign(MIDDLE)
        , m_text(caption) {
            m_backgroundColor.r = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.g = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.b = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.a = 1.f;

            m_textColor.r = 0.f;
            m_textColor.g = 0.f;
            m_textColor.b = 0.f;
            m_textColor.a = 1.f;
            setSizeBehaviour(Component::FIXED, Component::FIXED);
            addEventHandler(new EVENT::MouseClickToFirstResponder<Button>(*this));
            addEventHandler(new EVENT::MouseClickHandler<Button>(*this));
            addEventHandler(new EVENT::DesaturateBackgroundOnHover<Button>(*this));
        }

        Button::~Button() {
        }

        bool Button::click(const click_slot_type& s) {
            boost::signals2::connection c = onClick.connect(s);
            if (c.connected())
                return true;
            return false;
        }

        void Button::setText(const std::string& text) {
            m_text = text;
            if (m_componentView)
                m_componentView->update(*this);
        }

        void Button::setTextColor(float r, float g, float b, float a) {
            m_textColor.r = r;
            m_textColor.g = g;
            m_textColor.b = b;
            m_textColor.a = a;
        }

        void Button::setBackgroundColor(float r, float g, float b, float a) {
            m_backgroundColor.r = r;
            m_backgroundColor.g = g;
            m_backgroundColor.b = b;
            m_backgroundColor.a = a;
        }

        void Button::setBackgroundColor(const MATH::vec4& color) {
            m_backgroundColor = color;
        }

        const MATH::vec4& Button::getBackgroundColor() const {
            return m_backgroundColor;
        }

    }
}
