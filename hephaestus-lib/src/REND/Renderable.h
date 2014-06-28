/* 
 * File:   Renderable.h
 * Author: chris
 *
 * Created on March 23, 2014, 5:26 PM
 */

#ifndef RENDERABLE_H
#define	RENDERABLE_H

#include "ShaderProgramInstance.h"
#include "Renderer.h"

namespace REND {
    class Renderer;
    class RenderBuffer;
    class UniformSetting;
    class RenderableInstance;
    class Renderable {
    public:
        Renderable(RenderBuffer* renderBuffer, ShaderProgramInstance shaderInstance);
        virtual ~Renderable();
        
        //virtual RenderableInstance* createInstance() const;
        
        RenderBuffer* getRenderBuffer() { return m_renderBuffer; }
        void setRenderBuffer(RenderBuffer* renderBuffer);
        
        const ShaderProgramInstance& getShaderInstance() const { return m_shaderInstance; }
        
        virtual void activateProgram(Renderer& renderer) const;
        virtual void draw(Renderer& renderer) const;
        /*
        inline void addToRenderGroup(int group) { m_renderGroups.set(group, true); }
        inline void removeFromRenderGroup(int group) { m_renderGroups.set(group, false); }
        
        inline bool shouldRender(const REND::Renderer& renderer) const { 
            int renderGroup = renderer.getRenderGroup();
            return ( ( renderGroup < 0 ) || m_renderGroups.test(renderGroup) );
        }*/
    protected:
        RenderBuffer* m_renderBuffer;
        ShaderProgramInstance m_shaderInstance;
        UniformSetting* m_projectionMatrix;
        UniformSetting* m_modelMatrix;
        
    };
}
#endif	/* RENDERABLE_H */

