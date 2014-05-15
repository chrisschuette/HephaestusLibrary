/* 
 * File:   GLSprite.cpp
 * Author: chris
 * 
 * Created on March 23, 2014, 6:29 PM
 */

#include "GLSprite.h"
#include "GLTexture.h"
#include "../ERR/ERR.h"
#include "../MATH/vec234.h"
#include "GLShaderProgram.h"
#include "GUIRenderer.h"

namespace GL {

    GLSprite::GLSprite(const SYS::Handle<REND::Texture>& texture, const REND::ShaderProgram* shaderProgram)
    : REND::Sprite(texture, shaderProgram)
    , m_vertexBuffer("vertex:2f,tex_coord:2f") {
        GLTexture* gl_texture = static_cast<GLTexture*> (*m_texture);

        if (!gl_texture)
            THROWS("No texture.");

        // fill vertex buffer
        GLuint indices[6] = {0, 1, 2, 0, 3, 1};
        MATH::vec4 vertices[4] = {
            {0, 0, 0, 0},
            {gl_texture->getTextureWidth(), gl_texture->getTextureHeight(), 1, 1},
            {0, gl_texture->getTextureHeight(), 0, 1},
            {gl_texture->getTextureWidth(), 0, 1, 0}
        };
        m_vertexBuffer.push_back(vertices, 4, indices, 6);
    }

    GLSprite::~GLSprite() {
    }

    void GLSprite::draw(const REND::Renderer& r) {

        GLTexture* texture = static_cast<GLTexture*> (*m_texture);
        const  GLShaderProgram* shaderProgram = static_cast<const GLShaderProgram*> (m_shaderProgram);
        const GL::GUIRenderer& renderer = static_cast<const GL::GUIRenderer&> (r);
        
        if (!texture)
            THROWS("No texture.");
        if (!shaderProgram)
            THROWS("No shader.");

        // activate texture & shader
        shaderProgram->activate();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->getTextureName());
        shaderProgram->setUniformi("texture", 0);
        shaderProgram->setUniform("projection", renderer.GetProjectionMatrix());
        shaderProgram->setUniform("model", renderer.GetModelMatrix());
        //draw
        m_vertexBuffer.render(GL_TRIANGLES);

    }

}
