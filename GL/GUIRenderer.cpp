/* 
 * File:   GUIRenderer.cpp
 * Author: chris
 * 
 * Created on February 10, 2014, 5:10 PM
 */

#include "GUIRenderer.h"
#include "GLShaderManager.h"

namespace GL {

    GUIRenderer::GUIRenderer(REND::ShaderManager& shaderManager, REND::FONTS::FontManager& fontManager)
    : GUI::Renderer(shaderManager, fontManager)
    , m_frustum(0, 1, 0, 1, -1, 1)
    , m_debugScreen("vertex:2f,tex_coord:2f") {
        m_modelMatrixStack.LoadIdentity();

        GLuint indices[6] = {0, 1, 2, 0, 3, 1};
        typedef struct {
            float x, y, u, v;
        } vertex_t;
        vertex_t vertices[4] = {
            { -1, -1, 0, 1},
            {  1,  1, 1, 0},
            { -1,  1, 0, 0},
            {  1, -1, 1, 1}
        };
        m_debugScreen.push_back(vertices, 4, indices, 6);
    }

    GUIRenderer::~GUIRenderer() {
    }

    void GUIRenderer::PushMatrix() {
        m_modelMatrixStack.PushMatrix();
    }

    void GUIRenderer::PopMatrix() {
        m_modelMatrixStack.PopMatrix();
    }

    void GUIRenderer::Translate(int x, int y) {
        m_modelMatrixStack.Translate(x, y, 0);
    }

    int GUIRenderer::getScreenWidth() {
        return m_screenDimensions.x;
    }

    int GUIRenderer::getScreenHeight() {
        return m_screenDimensions.y;
    }

    void GUIRenderer::setScreenDimensions(int w, int h) {
        glViewport(0, 0, w, h);
        m_screenDimensions = GEOMETRY::Vec2<int>(w, h);
        m_frustum.SetOrthographic(0, w, h, 0, -1, 1);
    }

    const M3DMatrix44f& GUIRenderer::GetProjectionMatrix() const {
        return m_frustum.GetProjectionMatrix();
    }

    const M3DMatrix44f& GUIRenderer::GetModelMatrix() const {
        return m_modelMatrixStack.GetMatrix();
    }

    unsigned int GUIRenderer::readPixelFromStencilBuffer(const GEOMETRY::Vec2<int>& pos) {
        GLuint index;
        glReadPixels(pos.x, pos.y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        return index;
    }

    void GUIRenderer::debugTexture(const GL::GLShaderProgram& program, unsigned int texture) {
        program.activate();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture );
        program.setUniformi("texture", 0);
        m_debugScreen.render(GL_TRIANGLES);
    }

    
}
