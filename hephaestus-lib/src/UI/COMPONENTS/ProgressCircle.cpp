/* 
 * File:   ProgressCircle.cpp
 * Author: chris
 * 
 * Created on June 10, 2014, 10:54 PM
 */

#include "ProgressCircle.h"
#include "../ComponentView.h"
#include <cstdlib>

namespace UI {
    namespace COMPONENTS {

        ProgressCircle::ProgressCircle()
        : View("ProgressCircle")
        , m_maxValue(100)
        , m_value(50)
        , m_thickness(10)
        , m_background(false) {
            m_backgroundColor.r = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.g = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.b = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.a = 1.f;

            m_circleColor.r = (float) (55 + (rand() % 200)) / 255.f;
            m_circleColor.g = (float) (55 + (rand() % 200)) / 255.f;
            m_circleColor.b = (float) (55 + (rand() % 200)) / 255.f;
            m_circleColor.a = 1.f;
        }

        ProgressCircle::~ProgressCircle() {
        }

        void ProgressCircle::setBackgroundColor(float r, float g, float b, float a) {
            m_backgroundColor.r = r;
            m_backgroundColor.g = g;
            m_backgroundColor.b = b;
            m_backgroundColor.a = a;
        }

        void ProgressCircle::setCircleColor(float r, float g, float b, float a) {
            m_circleColor.r = r;
            m_circleColor.g = g;
            m_circleColor.b = b;
            m_circleColor.a = a;
        }

        void ProgressCircle::setMaximumValue(int maxValue) {
            if (maxValue != m_maxValue) {
                m_maxValue = maxValue;
                m_value = std::min(m_value, m_maxValue);
                if (m_componentView)
                    m_componentView->update(*this);
            }
        }

        void ProgressCircle::setValue(int value) {
            if (value != m_value) {
                m_value = std::min(value, m_maxValue);
                if (m_componentView)
                    m_componentView->update(*this);
            }
        }
    }
}
