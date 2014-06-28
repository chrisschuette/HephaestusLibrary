/* 
 * File:   GradientSprite.cpp
 * Author: chris
 * 
 * Created on June 18, 2014, 5:28 PM
 */

#include "GradientSprite.h"
#include "GLVertexBuffer.h"
#include "../ERR/ERR.h"
#include "../LOG/Core.h"
#include "GLTexture.h"
#include "GLShaderProgram.h"

#define NAME "GradientSprite"

namespace GL {

    GradientSprite::GradientSprite(const SYS::Handle<REND::Texture>& texture, REND::ShaderProgramInstance shaderProgram)
    : REND::GradientSprite(new GL::GLVertexBuffer("vertex:2f,tex_coord:2f"), texture, shaderProgram) {
        // set up the render buffer
        GL::GLVertexBuffer* vb = static_cast<GL::GLVertexBuffer*> (m_renderBuffer);
        if (texture.get() == 0)
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

    GradientSprite::~GradientSprite() {
    }

    void GradientSprite::draw(REND::Renderer& renderer) const {
        // set up texturing
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, static_cast<const GL::GLTexture*> (m_texture.get())->getTextureName());
        int t0 = 0;
        m_sprite->set(&t0);
        const GL::GLShaderProgram* shaderProgram = static_cast<const GL::GLShaderProgram*> (m_shaderInstance->getInstance());
        shaderProgram->setUniformi("N", m_N);
            for (int i = 0; i < m_N; i++) {
                shaderProgram->setUniformf(m_stops[i].position_name, m_stops[i].position);
                shaderProgram->setUniformf(m_stops[i].color_name, m_stops[i].rgba.r, m_stops[i].rgba.g, m_stops[i].rgba.b, m_stops[i].rgba.a);
            }

        m_renderBuffer->draw();
    }


}