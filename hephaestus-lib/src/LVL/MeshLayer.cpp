/* 
 * File:   MeshLayer.cpp
 * Author: chris
 * 
 * Created on June 8, 2014, 4:34 PM
 */

#include "MeshLayer.h"

namespace LVL {

    MeshLayer::MeshLayer(LVL::Context& ctx) : Layer(ctx) {
    }

    MeshLayer::~MeshLayer() {
    }
    
    void MeshLayer::render(REND::Renderer& renderer, LVL::Context& context) {
        for(std::list<REND::SHAPES::MeshInstance>::iterator i = m_meshInstances.begin(), e = m_meshInstances.end(); i != e; ++i)
            (*i).draw(renderer);
    }

}
