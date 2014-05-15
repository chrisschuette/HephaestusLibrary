/* 
 * File:   Renderer.cpp
 * Author: chris
 * 
 * Created on February 10, 2014, 5:03 PM
 */

#include "Renderer.h"

namespace GUI {
    Renderer::Renderer(REND::ShaderManager& shaderManager,REND::FONTS::FontManager& fontManager)
    : REND::Renderer()
    , m_shaderManager(shaderManager)
    , m_fontManager(fontManager)
    {
    }

    Renderer::~Renderer() {
    }
}
