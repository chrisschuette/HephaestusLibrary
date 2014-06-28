/* 
 * File:   MeshInstance.cpp
 * Author: chris
 * 
 * Created on June 2, 2014, 2:00 PM
 */

#include "MeshInstance.h"
#include "../../REND/Renderer.h"
#include <cmath>
#include <assert.h>
#include <string.h>

#define RAD2DEG 57.2957795131

namespace REND {
    namespace SHAPES {

        MeshInstance::MeshInstance(const SYS::Handle<REND::SHAPES::Mesh>& handle) : SYS::Handle<REND::SHAPES::Mesh>(handle), m_hidden(0), m_nRenderables(-1) {
            m_position.x = 0;
            m_position.y = 0;
            m_angle = 0;
            if (this->get()) {
                m_nRenderables = this->get()->getRenderableCount();
                m_hidden = new bool[m_nRenderables];
                memset(m_hidden, 0, m_nRenderables);
            }
        }

        MeshInstance::MeshInstance(const MeshInstance& orig) : SYS::Handle<REND::SHAPES::Mesh>(orig) {
            m_nRenderables = orig.m_nRenderables;
            m_position = orig.m_position;
            m_angle = orig.m_angle;
            m_hidden = 0;
            if (orig.m_hidden && (m_nRenderables > 0)) {
                m_hidden = new bool[m_nRenderables];
                memcpy(m_hidden, orig.m_hidden, sizeof (bool) * m_nRenderables);
            }
        }

        MeshInstance& MeshInstance::operator=(const MeshInstance& orig) {
            if (m_hidden)
                delete [] m_hidden;


            m_nRenderables = orig.m_nRenderables;
            m_position = orig.m_position;
            m_angle = orig.m_angle;
            m_hidden = 0;
            if (orig.m_hidden && (m_nRenderables > 0)) {
                m_hidden = new bool[m_nRenderables];
                memcpy(m_hidden, orig.m_hidden, sizeof (bool) * m_nRenderables);
            }
            return *this;
        }

        MeshInstance::~MeshInstance() {
            if (m_hidden)
                delete [] m_hidden;
        }

        bool MeshInstance::isHidden(int n) {
            assert(m_hidden);
            assert(n >= 0);
            assert(n < m_nRenderables);
            return m_hidden[n];
        }

        void MeshInstance::setHidden(int n, bool hidden) {
            assert(m_hidden);
            assert(n >= 0);
            assert(n < m_nRenderables);
            m_hidden[n] = hidden;
        }

        inline bool MeshInstance::shouldRender(const REND::Renderer& renderer) const {
            int renderGroup = renderer.getRenderGroup();
            return ( (renderGroup < 0) || m_renderGroups.test(renderGroup));
        }

        void MeshInstance::draw(Renderer& renderer) {
            if (shouldRender(renderer)) {
                renderer.PushMatrix();
                renderer.Translate(m_position.x, m_position.y, 0);
                renderer.RotateZ(m_angle * RAD2DEG);
                if (this->operator *())
                    this->operator *()->draw(renderer, m_hidden);
                renderer.PopMatrix();
            }
        }
    }
}
