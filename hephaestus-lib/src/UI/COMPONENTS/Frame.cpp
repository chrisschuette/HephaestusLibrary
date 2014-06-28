/* 
 * File:   Frame.cpp
 * Author: chris
 * 
 * Created on May 23, 2014, 9:33 PM
 */

#include "Frame.h"
#include <cstdlib>

namespace UI {
    namespace COMPONENTS {

        Frame::Frame() : View("Frame"), m_background(false) {
            m_backgroundColor.r = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.g = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.b = (float) (55 + (rand() % 200)) / 255.f;
            m_backgroundColor.a = 1.f;

            this->setMinimumSize(0, 0);
            this->setMaximumSize(-1, -1);
            this->setSizeBehaviour(EXPAND, EXPAND);
        }

        Frame::~Frame() {
        }

        void Frame::setBackground(bool background) {
            m_background = background;
        }

        void Frame::setBackgroundColor(float r, float g, float b, float a) {
            m_backgroundColor.r = r;
            m_backgroundColor.g = g;
            m_backgroundColor.b = b;
            m_backgroundColor.a = a;
        }


    }
}
