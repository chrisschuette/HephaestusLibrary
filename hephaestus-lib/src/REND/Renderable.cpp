/* 
 * File:   Renderable.cpp
 * Author: chris
 * 
 * Created on March 23, 2014, 5:26 PM
 */

#include "Renderable.h"
#include "RenderBuffer.h"
#include "ShaderProgram.h"
#include "UniformSetting.h"
#include "RenderableInstance.h"
#include "Renderer.h"

namespace REND {

    Renderable::Renderable(RenderBuffer* renderBuffer, ShaderProgramInstance shaderInstance)
    : m_renderBuffer(renderBuffer)
    , m_shaderInstance(shaderInstance)
    , m_projectionMatrix(0)
    , m_modelMatrix(0) {
        if (*m_shaderInstance) {
            m_projectionMatrix = m_shaderInstance->createUniformSetting("projection", false);
            m_modelMatrix = m_shaderInstance->createUniformSetting("model", false);
        }
    }

    Renderable::~Renderable() {
        if (m_renderBuffer)
            delete m_renderBuffer;
        if (m_projectionMatrix)
            delete m_projectionMatrix;
        if (m_modelMatrix)
            delete m_modelMatrix;
    }
/*
    RenderableInstance* Renderable::createInstance() const {
        return new RenderableInstance(*this);
    }
  */  
    void Renderable::setRenderBuffer(RenderBuffer* renderBuffer) {
        if(m_renderBuffer)
            delete m_renderBuffer;
        m_renderBuffer = renderBuffer;
    }


    void Renderable::activateProgram(Renderer& renderer) const {
        if (*m_shaderInstance && m_modelMatrix && m_projectionMatrix) {
            m_shaderInstance->activate();
            renderer.setModelMatrix(*m_modelMatrix);
            renderer.setProjectionMatrix(*m_projectionMatrix);
        }
    }

    void Renderable::draw(Renderer& renderer) const {
        if (/*shouldRender(renderer) && */*m_shaderInstance && m_renderBuffer)
            m_renderBuffer->draw();
    }

}
