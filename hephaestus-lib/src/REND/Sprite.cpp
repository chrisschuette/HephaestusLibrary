/* 
 * File:   Sprite.cpp
 * Author: chris
 * 
 * Created on March 23, 2014, 5:27 PM
 */

#include "Sprite.h"

namespace REND {

    Sprite::Sprite(RenderBuffer* renderBuffer, const SYS::Handle<REND::Texture>& texture, ShaderProgramInstance shaderProgram)
    : REND::Renderable(renderBuffer, shaderProgram)
    , m_texture(texture) {
        m_sprite = shaderProgram.createUniformSetting("sprite", false);
    }

    Sprite::~Sprite() {
        if(m_sprite)
            delete m_sprite;
    }
    
    int Sprite::getWidth() const {
        if(m_texture.get())
            return m_texture->getTextureWidth();
        else
            return -1;
    }
    
    int Sprite::getHeight() const {
                if(m_texture.get())
            return m_texture->getTextureHeight();
        else
            return -1;
    }
}
