/* 
 * File:   VisualInstance.cpp
 * Author: chris
 * 
 * Created on June 23, 2013, 5:51 PM
 */

#include "VisualInstance.h"
#include "Visual.h"

namespace VISUAL {

    VisualInstance::VisualInstance(const Visual& visual)
    : m_visual(visual) {
    }

    VisualInstance::~VisualInstance() {
    }
    
    void VisualInstance::render(REND::Renderer& renderer) const {
        m_visual.render(*this, renderer);
    }

}
