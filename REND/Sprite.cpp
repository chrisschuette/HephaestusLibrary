/* 
 * File:   Sprite.cpp
 * Author: chris
 * 
 * Created on March 23, 2014, 5:27 PM
 */

#include "Sprite.h"

namespace REND {
    Sprite::Sprite(const SYS::Handle<REND::Texture>& texture, const ShaderProgram* shaderProgram)
    : REND::Renderable()
    , m_texture(texture)
    , m_shaderProgram(shaderProgram)
    {
    }

    Sprite::~Sprite() {
    }
}
