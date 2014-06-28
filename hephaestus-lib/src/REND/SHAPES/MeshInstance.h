/* 
 * File:   MeshInstance.h
 * Author: chris
 *
 * Created on June 2, 2014, 2:00 PM
 */

#ifndef MESHINSTANCE_H
#define	MESHINSTANCE_H

#include "../../SYS/Handle.h"
#include "Mesh.h"
#include "../../MATH/vec234.h"
#include <bitset>

namespace REND {
    namespace SHAPES {
        class Mesh;

        class MeshInstance : public SYS::Handle<REND::SHAPES::Mesh> {
        public:
            MeshInstance(const SYS::Handle<REND::SHAPES::Mesh>& handle);
            MeshInstance(const MeshInstance& orig);
            MeshInstance& operator=(const MeshInstance& orig);
            virtual ~MeshInstance();



            void draw(Renderer& renderer);

            void setPosition(float x, float y) {
                m_position.x = x;
                m_position.y = y;
            }

            void setPosition(const MATH::vec2& position) {
                m_position = position;
            }

            const MATH::vec2& getPosition() const {
                return m_position;
            }

            void setOrientation(float angle) {
                m_angle = angle;
            }

            float getOrientation() const {
                return m_angle;
            }

            bool isHidden(int n);
            void setHidden(int n, bool hidden);

            inline void addToRenderGroup(int group) {
                m_renderGroups.set(group, true);
            }

            inline void removeFromRenderGroup(int group) {
                m_renderGroups.set(group, false);
            }

            inline bool shouldRender(const REND::Renderer& renderer) const;

        private:
            MATH::vec2 m_position;
            float m_angle;
            bool * m_hidden;
            int m_nRenderables;

            std::bitset<8> m_renderGroups;

        };
    }
}
#endif	/* MESHINSTANCE_H */

