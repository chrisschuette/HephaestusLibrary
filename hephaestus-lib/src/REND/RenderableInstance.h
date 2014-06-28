/* 
 * File:   RenderableInstance.h
 * Author: chris
 *
 * Created on June 2, 2014, 12:40 AM
 */

#ifndef RENDERABLEINSTANCE_H
#define	RENDERABLEINSTANCE_H

#include <list>

namespace REND {
    class Renderer;
    class Renderable;
    class UniformSetting;
    class RenderableInstance {
    public:
        RenderableInstance(const Renderable& renderable);
        virtual ~RenderableInstance();
        
        void addUniformSetting(UniformSetting* uniformSetting);
        
        virtual void draw(Renderer& renderer);
    private:
        const Renderable& m_renderable;
        std::list<UniformSetting*> m_uniformSettings;
    };
}
#endif	/* RENDERABLEINSTANCE_H */

