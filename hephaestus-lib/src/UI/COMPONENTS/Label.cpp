/* 
 * File:   Label.cpp
 * Author: chris
 * 
 * Created on June 11, 2014, 10:57 PM
 */

#include "Label.h"
#include "../ComponentView.h"
#include <cstdlib>

namespace UI {
    namespace COMPONENTS {

        Label::Label()
        : Component("Label")
        , m_textAlign(CENTER)
        , m_VTextAlign(MIDDLE)
        , m_background(false) {
            m_backgroundColor.r = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.g = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.b = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.a = 1.f;

            m_textColor.r = 0.f;
            m_textColor.g = 0.f;
            m_textColor.b = 0.f;
            m_textColor.a = 1.f;
        }

        Label::Label(std::string text)
        : Component("Label")
        , m_textAlign(CENTER)
        , m_VTextAlign(MIDDLE)
        , m_text(text)
        , m_background(false) {
            m_backgroundColor.r = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.g = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.b = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.a = 1.f;

            m_textColor.r = 0.f;
            m_textColor.g = 0.f;
            m_textColor.b = 0.f;
            m_textColor.a = 1.f;
        }

        Label::~Label() {
        }

        void Label::setText(const std::string& text) {
            if (text != m_text) {
                m_text = text;
                if (m_componentView)
                    m_componentView->update(*this);
            }
        }

        void Label::setBackgroundColor(float r, float g, float b, float a) {
            m_backgroundColor.r = r;
            m_backgroundColor.g = g;
            m_backgroundColor.b = b;
            m_backgroundColor.a = a;
        }

        const MATH::vec4& Label::getBackgroundColor() const {
            return m_backgroundColor;
        }
    }
}
