/* 
 * File:   MeshLayer.h
 * Author: chris
 *
 * Created on June 8, 2014, 4:34 PM
 */

#ifndef MESHLAYER_H
#define	MESHLAYER_H

#include "Layer.h"
#include "../REND/SHAPES/MeshInstance.h"

#include <list>

namespace LVL {
    class Context;

    class MeshLayer : public Layer {
    public:
        MeshLayer(LVL::Context& ctx);
        virtual ~MeshLayer();
        virtual void update(unsigned long int time, unsigned long int diff) {}
        virtual void render(REND::Renderer& renderer, LVL::Context& context);        
        void addMeshInstance(const REND::SHAPES::MeshInstance& meshInstance) {
            m_meshInstances.push_back(meshInstance);
        }
    protected:
        std::list<REND::SHAPES::MeshInstance> m_meshInstances;
    };
}
#endif	/* MESHLAYER_H */

