/* 
 * File:   Renderer.cpp
 * Author: chris
 * 
 * Created on May 20, 2014, 8:48 PM
 */

#include "Renderer.h"
#include "UniformSetting.h"
#include "../LOG/Core.h"
#include "GLTexture.h"

#include <GL/glew.h>

#define NAME "Renderer"

namespace GL {

    Renderer::Renderer()
    : REND::Renderer()
    , m_frustum(0, 1, 0, 1, -1, 1)
    , m_screen("vertex:2f")
    , m_screen_tex("vertex:2f,tex_coord:2f") {
        // set up the render buffer
        GLuint indices[6] = {0, 1, 2, 0, 3, 1};
        MATH::vec4 vertices[4] = {
            {-1, -1},
            {1, 1},
            {-1, 1},
            {1, -1}
        };
        MATH::vec4 vertices2[4] = {
            {-1, -1, 0, 0},
            {1, 1, 1, 1},
            {-1, 1, 0, 1},
            {1, -1, 1, 0}
        };
        m_screen.push_back(vertices, 4, indices, 6);
        m_screen_tex.push_back(vertices2, 4, indices, 6);
        m_modelMatrixStack.LoadIdentity();
    }

    Renderer::~Renderer() {
    }

    void Renderer::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    const M3DMatrix44f& Renderer::GetProjectionMatrix() const {
        return m_frustum.GetProjectionMatrix();
    }

    const M3DMatrix44f& Renderer::GetModelMatrix() const {
        return m_modelMatrixStack.GetMatrix();
    }

    void Renderer::setProjectionMatrix(const REND::UniformSetting& uniformSetting) {
        const GL::UniformSetting<4, float, 'M'>& u = static_cast<const GL::UniformSetting<4, float, 'M'>&> (uniformSetting);
        u.set(GetProjectionMatrix());
    }

    void Renderer::setModelMatrix(const REND::UniformSetting& uniformSetting) {
        const GL::UniformSetting<4, float, 'M'>& u = static_cast<const GL::UniformSetting<4, float, 'M'>&> (uniformSetting);
        u.set(GetModelMatrix());
    }

    void Renderer::setViewport(int minX, int maxX, int minY, int maxY) {
        glViewport(minX, minY, maxX, maxY);
    }

    void Renderer::setOrthographic(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
        m_frustum.SetOrthographic(minX, maxX, minY, maxY, minZ, maxZ);
    }

    void Renderer::Translate(int dx, int dy, int dz) {
        m_modelMatrixStack.Translate(dx, dy, dz);
    }

    void Renderer::RotateZ(float angle) {
        m_modelMatrixStack.Rotate(angle, 0, 0, 1);
    }

    void Renderer::PushMatrix() {
        m_modelMatrixStack.PushMatrix();
    }

    void Renderer::PopMatrix() {
        m_modelMatrixStack.PopMatrix();
    }

    void Renderer::RenderTextureToScreen(REND::Texture* texture, REND::UniformSetting* textureSetting) {
        GL::GLTexture* gltexture = static_cast<GL::GLTexture*> (texture);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, static_cast<const GL::GLTexture*> (texture)->getTextureName());
        int t0 = 0;
        textureSetting->set(&t0);
        m_screen_tex.draw();
    }

    void Renderer::RenderTextureToTexture(REND::Texture* source, REND::Texture* destination, REND::UniformSetting* textureSetting) {
        //save
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);


        GL::GLTexture* source_texture = static_cast<GL::GLTexture*> (source);
        GL::GLTexture* destination_texture = static_cast<GL::GLTexture*> (destination);

        // prepare
        if (!destination_texture) {
            L(error) << "Invalid texture";
            return;
        }

        // bind the texture
        glBindTexture(GL_TEXTURE_2D, destination_texture->getTextureName());



        // create and bind a framebuffer object
        GLuint FBO;
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, destination_texture->getTextureName(), 0);

        GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

        // check FBO status
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            L(error) << "Incomplete FBO.";
            return;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glViewport(0, 0, destination_texture->getTextureWidth(), destination_texture->getTextureHeight()); // Render on the whole framebuffer, complete from the lower left corner to the upp
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);



        // draw stuff
        clear();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, source_texture->getTextureName());
        int t0 = 0;
        textureSetting->set(&t0);
        m_screen_tex.draw();



        // switch back to window-system-provided framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDeleteFramebuffers(1, &FBO);
        GLenum windowBuff [] = {GL_FRONT_LEFT};
        glDrawBuffers(1, windowBuff);


        // restore old viewport
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]); // Render on the whole framebuffer, complete from the lower left corner to the upp

    }

    void Renderer::RenderToTexture(RenderDelegate renderDelegate, REND::Texture* texture) {

        //save
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        GL::GLTexture* gltexture = static_cast<GL::GLTexture*> (texture);

        // prepare
        if (!gltexture) {
            L(error) << "Invalid texture";
            return;
        }

        // bind the texture
        glBindTexture(GL_TEXTURE_2D, gltexture->getTextureName());

        // create and bind a framebuffer object
        GLuint FBO;
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gltexture->getTextureName(), 0);

        GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

        // check FBO status
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            L(error) << "Incomplete FBO.";
            return;
        }

        // Render to our framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glViewport(0, 0, gltexture->getTextureWidth(), gltexture->getTextureHeight()); // Render on the whole framebuffer, complete from the lower left corner to the upp
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);

                clear();
renderDelegate();

        // restore
        // switch back to window-system-provided framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDeleteFramebuffers(1, &FBO);
        GLenum windowBuff [] = {GL_FRONT_LEFT};
        glDrawBuffers(1, windowBuff);
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]); // Render on the whole framebuffer, complete from the lower left corner to the upp

    }

}
