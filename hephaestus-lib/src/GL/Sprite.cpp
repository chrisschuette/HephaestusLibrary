/* 
 * File:   Sprite.cpp
 * Author: chris
 * 
 * Created on June 14, 2014, 12:23 PM
 */

#include "Sprite.h"
#include "GLTexture.h"
#include "GLVertexBuffer.h"
#include "../ERR/ERR.h"
#include "../LOG/Core.h"

#define NAME "Sprite"

namespace GL {

    Sprite::Sprite(const SYS::Handle<REND::Texture>& texture, REND::ShaderProgramInstance shaderProgram)
    : REND::Sprite(new GL::GLVertexBuffer("vertex:2f,tex_coord:2f"), texture, shaderProgram) {
        // set up the render buffer
        GL::GLVertexBuffer* vb = static_cast<GL::GLVertexBuffer*> (m_renderBuffer);
        if(texture.get() == 0)
            THROWS("invalid texture!");
        int W = texture->getTextureWidth();
        int H = texture->getTextureHeight();
        L(normal) << W << " x " << H;
        GLuint indices[6] = {0, 1, 2, 0, 3, 1};
        MATH::vec4 vertices2[4] = {
            {0, 0, 0, 1},
            {W, -H, 1, 0},
            {0, -H, 0, 0},
            {W, 0, 1, 1}
        };
        vb->push_back(vertices2, 4, indices, 6);
    }

    Sprite::~Sprite() {
    }

    void Sprite::draw(REND::Renderer& renderer) const {
        // set up texturing
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, static_cast<const GL::GLTexture*> (m_texture.get())->getTextureName());
        int t0 = 0;
        m_sprite->set(&t0);

        m_renderBuffer->draw();
    }

}
