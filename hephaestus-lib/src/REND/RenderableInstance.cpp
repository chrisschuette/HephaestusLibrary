/* 
 * File:   RenderableInstance.cpp
 * Author: chris
 * 
 * Created on June 2, 2014, 12:40 AM
 */

#include "RenderableInstance.h"
#include "UniformSetting.h"
#include "Renderable.h"

namespace REND {

    RenderableInstance::RenderableInstance(const Renderable& renderable) : m_renderable(renderable) {
    }

    RenderableInstance::~RenderableInstance() {
        for (std::list<UniformSetting*>::iterator i = m_uniformSettings.begin(), e = m_uniformSettings.end(); i != e; ++i)
            delete (*i);
    }

    void RenderableInstance::addUniformSetting(UniformSetting* uniformSetting) {
        m_uniformSettings.push_back(uniformSetting);
    }

    void RenderableInstance::draw(Renderer& renderer) {
        m_renderable.activateProgram(renderer);
        
        // set the instance uniforms
        for (std::list<UniformSetting*>::iterator i = m_uniformSettings.begin(), e = m_uniformSettings.end(); i != e; ++i)
            (*i)->set();
        
        m_renderable.draw(renderer);
    }

}
