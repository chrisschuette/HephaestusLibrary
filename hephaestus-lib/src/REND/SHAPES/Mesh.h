/* 
 * File:   Mesh.h
 * Author: chris
 *
 * Created on May 30, 2014, 5:56 PM
 */

#ifndef MESH_H
#define	MESH_H

namespace REND {
    class Renderer;
    class Renderable;
    class MeshInstance;
    namespace SHAPES {

        namespace Mesh_CONST {
            const int ALLOCATE_CHUNKS = 4;
        }

        class Mesh {
        public:
            Mesh();
            virtual ~Mesh();

            void draw(Renderer& renderer, bool* hidden = 0);

            void addRenderable(Renderable* renderable);

            inline const Renderable* getRenderables(int index) const {
                return m_renderables[index];
            }

            inline Renderable* getRenderable(int index) {
                return m_renderables[index];
            }

            int getRenderableCount() const {
                return m_nRenderables;
            }

        private:
            Renderable** m_renderables;
            int m_nRenderables;
            int m_nAllocated;
        };
    }
}
#endif	/* MESH_H */

