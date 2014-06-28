/* 
 * File:   Layer.cpp
 * Author: chris
 * 
 * Created on May 27, 2014, 12:27 PM
 */

#include "Layer.h"
#include "Context.h"
#include "Level.h"
#include "../GL/GLFrame.h"
#include "../GL/Camera.h"

#include <iostream>

namespace LVL {

    Layer::Layer(Context& context) : m_ctx(context), m_scrollFactorX(1), m_scrollFactorY(0) {

    }

    Layer::~Layer() {
    }

}
