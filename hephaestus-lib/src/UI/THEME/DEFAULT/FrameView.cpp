/* 
 * File:   FrameView.cpp
 * Author: chris
 * 
 * Created on May 23, 2014, 9:34 PM
 */

#include "FrameView.h"
#include "../../View.h"
#include "../../COMPONENTS/Frame.h"
#include "../../Context.h"
#include "../../../REND/Renderable.h"
#include "../../../REND/UniformSetting.h"

#include "../../../GL/GLShaderManager.h"
#include "../../../GL/GLVertexBuffer.h"

#include <iostream>

namespace UI {
    namespace THEME {
        namespace DEFAULT {

            FrameView::FrameView() : ComponentView() {
            }

            FrameView::~FrameView() {
                if(m_background)
                    delete m_background;
                if(m_backgroundColor)
                    delete m_backgroundColor;
            }

            ComponentView* FrameView::create(Component& cmp, Context& ctx) {
                View& view = static_cast<View&> (cmp);
                view.setContainerDimensions(view.getWidth() - 2 * view.getHPadding(), view.getHeight() - 2 * view.getVPadding());

                COMPONENTS::Frame& frame = static_cast<COMPONENTS::Frame&> (cmp);
                GL::GLShaderManager& shaderManager = static_cast<GL::GLShaderManager&> (ctx.getShaderManager());

                // create and fill the vertex buffer
                GL::GLVertexBuffer* backgroundBuffer = new GL::GLVertexBuffer("vertex:2f");
                GLuint indices[6] = {0, 1, 2, 0, 3, 1};
                MATH::vec2 vertices[4] = {
                    {0, 0},
                    {frame.getWidth() - 2 * cmp.getHPadding(), frame.getHeight() - 2 * cmp.getVPadding()},
                    {0, frame.getHeight() - 2 * cmp.getVPadding()},
                    {frame.getWidth() - 2 * cmp.getHPadding(), 0}
                };
                backgroundBuffer->push_back(vertices, 4, indices, 6);
                FrameView* frameView = new FrameView;
                frameView->m_background = new REND::Renderable(backgroundBuffer, ctx.getShaderManager().getShaderProgramInstance("flat"));
                frameView->m_backgroundColor = frameView->m_background->getShaderInstance().createUniformSetting("color", false);

                return frameView;
            }

            void FrameView::update(Component& component) {
                View& view = static_cast<View&> (component);
                view.setContainerDimensions(view.getWidth() - 2 * view.getHPadding(), view.getHeight() - 2 * view.getVPadding());
                if (m_background && m_background->getRenderBuffer()) {
                    GL::GLVertexBuffer* vb = static_cast<GL::GLVertexBuffer*> (m_background->getRenderBuffer());
                    int x = component.getWidth();
                    int y = component.getHeight();
                    MATH::vec2 vertex;
                    vertex.x = 0;
                    vertex.y = 0;
                    vb->update_vertex(&vertex, 1);
                    vertex.x = x - 2 * component.getHPadding();
                    vertex.y = y - 2 * component.getVPadding();
                    vb->update_vertex(&vertex, 1);
                    vertex.x = 0;
                    vertex.y = y - 2 * component.getVPadding();
                    vb->update_vertex(&vertex, 2);
                    vertex.x = x - 2 * component.getHPadding();
                    vertex.y = 0;
                    vb->update_vertex(&vertex, 3);
                }
            }

            void FrameView::render(REND::Renderer& renderer, const Component& component) {
                const COMPONENTS::Frame& frame = static_cast<const COMPONENTS::Frame&> (component);
                if (m_background && m_backgroundColor && frame.hasBackground()) {
                    m_background->activateProgram(renderer);
                    m_backgroundColor->set(frame.getBackgroundColor().data);
                    m_background->draw(renderer);
                }
            }

        }
    }
}
