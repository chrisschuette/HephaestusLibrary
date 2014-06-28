/* 
 * File:   Mesh.cpp
 * Author: chris
 * 
 * Created on May 30, 2014, 5:56 PM
 */

#include "Mesh.h"
#include "../../LOG/Core.h"
#include "../Renderable.h"

#define NAME "Mesh"

namespace REND {
    namespace SHAPES {

        Mesh::Mesh()
        : m_renderables(new Renderable*[Mesh_CONST::ALLOCATE_CHUNKS])
        , m_nAllocated(Mesh_CONST::ALLOCATE_CHUNKS)
        , m_nRenderables(0) {
        }

        Mesh::~Mesh() {
            for (int i = 0; i < m_nRenderables; i++)
                delete m_renderables[i];
            delete [] m_renderables;
        }

        void Mesh::draw(Renderer& renderer, bool* hidden) {
            if (!hidden) {
                for (int i = 0; i < m_nRenderables; i++) {
                    m_renderables[i]->activateProgram(renderer);
                    m_renderables[i]->draw(renderer);
                }
            } else {
                for (int i = 0; i < m_nRenderables; i++) {
                    m_renderables[i]->activateProgram(renderer);
                    if (!hidden[i])
                        m_renderables[i]->draw(renderer);
                }
            }
        }

        void Mesh::addRenderable(Renderable * renderable) {
            if (m_nRenderables == m_nAllocated) { // need more space
                m_nAllocated = m_nRenderables + Mesh_CONST::ALLOCATE_CHUNKS;
                Renderable** renderables = new Renderable*[m_nAllocated];
                memcpy(renderables, m_renderables, sizeof (Renderable*) * m_nRenderables );
                delete [] m_renderables;
                m_renderables = renderables;
            }

            m_renderables[m_nRenderables] = renderable;
            m_nRenderables++;
        }
    }
}
