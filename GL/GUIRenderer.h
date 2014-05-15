/* 
 * File:   GUIRenderer.h
 * Author: chris
 *
 * Created on February 10, 2014, 5:10 PM
 */

#ifndef GUIRENDERER_H
#define	GUIRENDERER_H

#include "../GUI/Renderer.h"
#include "GLFrustum.h"
#include "../GEOMETRY/Vec2.h"
#include "GLMatrixStack.h"
#include "GLShaderProgram.h"
#include "GLVertexBuffer.h"

namespace GL {
    class GUIRenderer : public GUI::Renderer {
    public:
        GUIRenderer(REND::ShaderManager& shaderManager, REND::FONTS::FontManager& fontManager);
        virtual ~GUIRenderer();
        virtual void PushMatrix();
        virtual void PopMatrix();
        virtual void Translate(int x, int y);
        int getScreenWidth();
        int getScreenHeight();
        void setScreenDimensions(int w, int h);
        const M3DMatrix44f& GetProjectionMatrix() const;
        const M3DMatrix44f& GetModelMatrix()const ;
        unsigned int readPixelFromStencilBuffer(const GEOMETRY::Vec2<int>& pos);
        void debugTexture(const GL::GLShaderProgram& program, unsigned int texture);
    private:
        GL::GLFrustum m_frustum;
        GL::GLMatrixStack m_modelMatrixStack;
        GEOMETRY::Vec2<int> m_screenDimensions;
        GL::GLVertexBuffer m_debugScreen;
    };
}
#endif	/* GUIRENDERER_H */

