/* 
 * File:   AnimatedSprite.cpp
 * Author: chris
 * 
 * Created on June 20, 2014, 4:44 PM
 */

#include "AnimatedSprite.h"
#include "GLVertexBuffer.h"
#include "../ERR/ERR.h"
#include "../LOG/Core.h"
#include "../GL/GLTexture.h"

#define NAME "AnimatedSprite"

namespace GL {

    AnimatedSprite::AnimatedSprite(const SYS::Handle<REND::Texture>& texture, REND::ShaderProgramInstance shaderProgram, const MATH::ivec2& spriteDimensions)
    : REND::AnimatedSprite(new GLVertexBuffer("vertex:2f,tex_coord:2f"), texture, shaderProgram, spriteDimensions) {

        // set up the render buffer
        GLVertexBuffer* vb = static_cast<GLVertexBuffer*> (m_renderBuffer);
        if (texture.get() == 0)
            THROWS("invalid texture!");
        int W = spriteDimensions.x;
        int H = spriteDimensions.y;
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

    AnimatedSprite::~AnimatedSprite() {
    }

    void AnimatedSprite::draw(REND::Renderer& renderer) const {
        // set up texturing
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, static_cast<const GL::GLTexture*> (m_texture.get())->getTextureName());
        int t0 = 0;
        m_sprite->set(&t0);

        const Animation& currentAnimation = m_animations[m_currentAnimation];
        unsigned int frameIndex = currentAnimation.frames[m_currentFrame];
        const Frame& currentFrame = m_frames[frameIndex];
        float* T = (float*) m_TSetting->getRawData();
        T[0] = (float) currentFrame.x / (float) m_atlasDimensions.x; // x
        T[1] = (float) currentFrame.y / (float) m_atlasDimensions.y; // y
        T[2] = (float) m_spriteDimensions.x / (float) m_atlasDimensions.x; // tw
        T[3] = (float) m_spriteDimensions.y / (float) m_atlasDimensions.y; // th
        m_TSetting->set();
        
        int* flippedH = (int*) m_flippedHSetting->getRawData();
        flippedH[0] = (currentAnimation.flippedH ? GL_TRUE : GL_FALSE);
        m_flippedHSetting->set();
        
        int* flippedV = (int*) m_flippedVSetting->getRawData();
        flippedV[0] = (currentAnimation.flippedV ? GL_TRUE : GL_FALSE);
        m_flippedVSetting->set();
        
        m_renderBuffer->draw();
    }

}
