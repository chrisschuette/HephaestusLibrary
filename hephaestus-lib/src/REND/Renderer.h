/* 
 * File:   Renderer.h
 * Author: chris
 *
 * Created on June 23, 2013, 5:48 PM
 */

#ifndef RENDERER_H
#define	RENDERER_H

#include "../MATH/vec234.h"
#include "../UTIL/FastDelegate.h"
#include <bitset>

namespace REND {
    class Texture;
    class UniformSetting;
    class Renderer {
    public:
        typedef fastdelegate::FastDelegate0<> RenderDelegate;
    public:
        Renderer();
        virtual ~Renderer();
        
        virtual void setViewport(int minX,int maxX,int minY,int maxY) = 0;
        virtual void setOrthographic(float minX,float maxX,float minY,float maxY,float minZ,float maxZ) = 0;
        
        virtual void PushMatrix() = 0;
        virtual void PopMatrix() = 0;
        virtual void Translate(int dx, int dy, int dz) = 0;
        virtual void RotateZ(float angle) = 0;
        
        virtual void RenderToTexture(RenderDelegate renderDelegate, REND::Texture* texture) = 0;
        virtual void RenderTextureToTexture(REND::Texture* source, REND::Texture* destination, REND::UniformSetting* textureSetting) = 0;
        virtual void RenderTextureToScreen(REND::Texture* texture, REND::UniformSetting* textureSetting) = 0;

        
        virtual void setProjectionMatrix(const UniformSetting& uniformSetting) = 0;
        virtual void setModelMatrix(const UniformSetting& uniformSetting) = 0;
        
        virtual void clear() = 0;
        
        void setRenderGroup(int renderGroup) { m_renderGroup = renderGroup; }
        int getRenderGroup() const { return m_renderGroup; }

    private:
        int m_renderGroup;

    };
}
#endif	/* RENDERER_H */

