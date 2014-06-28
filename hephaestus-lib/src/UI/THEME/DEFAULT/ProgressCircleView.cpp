/* 
 * File:   ProgressCircleView.cpp
 * Author: chris
 * 
 * Created on June 10, 2014, 11:07 PM
 */

#include "ProgressCircleView.h"
#include "../../../REND/Renderable.h"
#include "../../../REND/UniformSetting.h"
#include "../../Component.h"
#include "../../COMPONENTS/ProgressCircle.h"
#include "../../../GL/GLShaderManager.h"
#include "../../Context.h"
#include "../../../GL/GLVertexBuffer.h"
#include "../../../LOG/Core.h"

#define NAME "ProgressCircleView"

namespace UI {
    namespace THEME {
        namespace DEFAULT {

            ProgressCircleView::ProgressCircleView()
            : ComponentView()
            , m_backgroundRenderable(0)
            , m_backgroundColor(0)
            , m_circleRenderable(0)
            , m_circleColor(0) {
            }

            ProgressCircleView::~ProgressCircleView() {
                if (m_backgroundRenderable)
                    delete m_backgroundRenderable;
                if (m_backgroundColor)
                    delete m_backgroundColor;
                if (m_circleRenderable)
                    delete m_circleRenderable;
                if (m_circleColor)
                    delete m_circleColor;
            }

            void ProgressCircleView::render(REND::Renderer& renderer, const Component& component) {
                const COMPONENTS::ProgressCircle& progressCircle = static_cast<const COMPONENTS::ProgressCircle&> (component);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                const MATH::vec4& bc = progressCircle.getBackgroundColor();
                const MATH::vec4& cc = progressCircle.getCircleColor();
                if (progressCircle.hasBackground()) {
                    m_backgroundRenderable->activateProgram(renderer);
                    m_backgroundColor->set(bc.data);
                    m_backgroundRenderable->draw(renderer);
                }
                m_circleRenderable->activateProgram(renderer);
                m_circleColor->set(cc.data);
                m_circleRenderable->draw(renderer);
            }

            void ProgressCircleView::update(Component& component) {
                COMPONENTS::ProgressCircle& progressCircle = static_cast<COMPONENTS::ProgressCircle&> (component);
                int x = component.getWidth();
                int y = component.getHeight();
                int R_O = std::min(progressCircle.getWidth() / 2 - component.getHPadding(), progressCircle.getHeight() / 2 - component.getVPadding());
                int R_I = std::max(0, R_O - progressCircle.getCircleThickness());
                if (m_backgroundRenderable && m_backgroundRenderable->getRenderBuffer()) {
                    GL::GLVertexBuffer* vb = static_cast<GL::GLVertexBuffer*> (m_backgroundRenderable->getRenderBuffer());
                    MATH::vec2 vertex;
                    vertex.x = 0;
                    vertex.y = 0;
                    vb->update_vertex(&vertex, 0);
                    vertex.x = x - 2 * component.getHPadding();
                    vertex.y = y - 2 * component.getVPadding();
                    vb->update_vertex(&vertex, 1);
                    vertex.x = 0;
                    vertex.y = y - 2 * component.getVPadding();
                    vb->update_vertex(&vertex, 2);
                    vertex.x = x - 2 * component.getHPadding();
                    vertex.y = 0;
                    vb->update_vertex(&vertex, 3);

                    vb = new GL::GLVertexBuffer("vertex:2f");
                    int value = progressCircle.getValue();
                    int maxValue = progressCircle.getMaximumValue();
                    GLuint indicesC[6 * value];
                    for (int i = 0; i < value; i++) {
                        indicesC[6 * i + 0] = 2 * i + 0;
                        indicesC[6 * i + 1] = 2 * i + 3;
                        indicesC[6 * i + 2] = 2 * i + 1;
                        indicesC[6 * i + 3] = 2 * i + 0;
                        indicesC[6 * i + 4] = 2 * i + 2;
                        indicesC[6 * i + 5] = 2 * i + 3;
                    }
                    float inc = 2.0 * M_PI / (float) (progressCircle.getMaximumValue());
                    MATH::vec2 verticesC[2 * value + 2];
                    for (int i = 0; i <= value; i++) {
                        verticesC[2 * i + 0].x = component.getWidth() / 2 - component.getHPadding() + std::sin(inc * i) * R_O;
                        verticesC[2 * i + 0].y = component.getHeight() / 2 - component.getVPadding() - std::cos(inc * i) * R_O;
                        verticesC[2 * i + 1].x = component.getWidth() / 2 - component.getHPadding() + std::sin(inc * i) * R_I;
                        verticesC[2 * i + 1].y = component.getHeight() / 2 - component.getVPadding() - std::cos(inc * i) * R_I;
                    }
                    if (value > 0)
                        vb->push_back(verticesC, 2 * value + 2, indicesC, 6 * value);
                    m_circleRenderable->setRenderBuffer(vb);
                }
                component.setMinimumSize(progressCircle.getCircleThickness() * 2, progressCircle.getCircleThickness() * 2);
                progressCircle.setContainerOrigin(component.getWidth() / 2 - component.getHPadding() - std::floor(std::sqrt(0.5f * R_I * R_I)), component.getHeight() / 2 - component.getVPadding() - std::floor(std::sqrt(0.5f * R_I * R_I)));
                progressCircle.setContainerDimensions(std::floor(std::sqrt(2.f * R_I * R_I)), std::floor(std::sqrt(2.f * R_I * R_I)));
            }

            ComponentView* ProgressCircleView::create(Component& cmp, Context& ctx) {
                COMPONENTS::ProgressCircle& progressCircle = static_cast<COMPONENTS::ProgressCircle&> (cmp);
                ProgressCircleView* progressCircleView = new ProgressCircleView;
                GL::GLShaderManager& shaderManager = static_cast<GL::GLShaderManager&> (ctx.getShaderManager());
                L(normal) << cmp.getWidth() << " " << cmp.getHeight();

                GL::GLVertexBuffer* backgroundBuffer = new GL::GLVertexBuffer("vertex:2f");
                GLuint indices[6] = {0, 1, 2, 0, 3, 1};
                MATH::vec2 vertices[4] = {
                    {0, 0},
                    {progressCircle.getWidth() - 2 * cmp.getHPadding(), progressCircle.getHeight() - 2 * cmp.getVPadding()},
                    {0, progressCircle.getHeight() - 2 * cmp.getVPadding()},
                    {progressCircle.getWidth() - 2 * cmp.getHPadding(), 0}
                };
                backgroundBuffer->push_back(vertices, 4, indices, 6);
                progressCircleView->m_backgroundRenderable = new REND::Renderable(backgroundBuffer, ctx.getShaderManager().getShaderProgramInstance("flat"));
                progressCircleView->m_backgroundColor = progressCircleView->m_backgroundRenderable->getShaderInstance().createUniformSetting("color", false);

                progressCircle.setMinimumSize(2 * progressCircle.getCircleThickness(), 2 * progressCircle.getCircleThickness());


                int R_O = std::min(progressCircle.getWidth() / 2 - cmp.getHPadding(), progressCircle.getHeight() / 2 - cmp.getVPadding());
                int R_I = std::max(0, R_O - progressCircle.getCircleThickness());

                GL::GLVertexBuffer* circleBuffer = new GL::GLVertexBuffer("vertex:2f");

                int value = progressCircle.getValue();
                int maxValue = progressCircle.getMaximumValue();
                GLuint indicesC[6 * value];
                for (int i = 0; i < value; i++) {
                    indicesC[6 * i + 0] = 2 * i + 0;
                    indicesC[6 * i + 1] = 2 * i + 3;
                    indicesC[6 * i + 2] = 2 * i + 1;
                    indicesC[6 * i + 3] = 2 * i + 0;
                    indicesC[6 * i + 4] = 2 * i + 2;
                    indicesC[6 * i + 5] = 2 * i + 3;
                }

                float inc = 2.0 * M_PI / (float) (progressCircle.getMaximumValue());
                MATH::vec2 verticesC[2 * value + 2];
                for (int i = 0; i <= value; i++) {
                    verticesC[2 * i + 0].x = cmp.getWidth() / 2 - cmp.getHPadding() + std::sin(inc * i) * R_O;
                    verticesC[2 * i + 0].y = cmp.getHeight() / 2 - cmp.getVPadding() - std::cos(inc * i) * R_O;
                    verticesC[2 * i + 1].x = cmp.getWidth() / 2 - cmp.getHPadding() + std::sin(inc * i) * R_I;
                    verticesC[2 * i + 1].y = cmp.getHeight() / 2 - cmp.getVPadding() - std::cos(inc * i) * R_I;
                }

                circleBuffer->push_back(verticesC, 2 * value + 2, indicesC, 6 * value);
                progressCircleView->m_circleRenderable = new REND::Renderable(circleBuffer, ctx.getShaderManager().getShaderProgramInstance("flat"));
                progressCircleView->m_circleColor = progressCircleView->m_circleRenderable->getShaderInstance().createUniformSetting("color", false);
                progressCircle.setContainerOrigin(cmp.getWidth() / 2 - cmp.getHPadding() - std::floor(std::sqrt(0.5f * R_I * R_I)), cmp.getHeight() / 2 - cmp.getVPadding() - std::floor(std::sqrt(0.5f * R_I * R_I)));
                progressCircle.setContainerDimensions(std::floor(std::sqrt(2.f * R_I * R_I)), std::floor(std::sqrt(2.f * R_I * R_I)));
                return progressCircleView;
            }


        }
    }
}
