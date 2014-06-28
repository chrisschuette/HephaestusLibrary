/* 
 * File:   Renderer.h
 * Author: chris
 *
 * Created on May 20, 2014, 8:48 PM
 */

#ifndef GLRENDERER_H
#define	GLRENDERER_H

#include "../REND/Renderer.h"
#include "GLFrustum.h"
#include "GLMatrixStack.h"
#include "GLVertexBuffer.h"
#include "GLShaderProgram.h"

namespace GL {

    class Renderer : public REND::Renderer {
    public:
        Renderer();
        virtual ~Renderer();

        virtual void setViewport(int minX, int maxX, int minY, int maxY);
        virtual void setOrthographic(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);

        const M3DMatrix44f& GetProjectionMatrix() const;
        const M3DMatrix44f& GetModelMatrix()const;

        virtual void setProjectionMatrix(const REND::UniformSetting& uniformSetting);
        virtual void setModelMatrix(const REND::UniformSetting& uniformSetting);

        virtual void RenderToTexture(RenderDelegate renderDelegate, REND::Texture* texture);
        virtual void RenderTextureToTexture(REND::Texture* source, REND::Texture* destination, REND::UniformSetting* textureSetting);
        virtual void RenderTextureToScreen(REND::Texture* texture, REND::UniformSetting* textureSetting);

        virtual void PushMatrix();
        virtual void PopMatrix();
        virtual void Translate(int dx, int dy, int dz);
        virtual void RotateZ(float angle);

        virtual void clear();

    private:
        GL::GLFrustum m_frustum;
        GL::GLMatrixStack m_modelMatrixStack;
        GL::GLVertexBuffer m_screen;
        GL::GLVertexBuffer m_screen_tex;
        
    };
}
#endif	/* GLRENDERER_H */

