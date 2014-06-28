/* 
 * File:   LabelView.cpp
 * Author: chris
 * 
 * Created on June 11, 2014, 10:58 PM
 */

#include "LabelView.h"
#include "../../Context.h"
#include "../../../REND/Renderable.h"
#include "../../../REND/UniformSetting.h"
#include "../../COMPONENTS/Label.h"

// OpenGL
#include "../../../GL/GLShaderManager.h"
#include "../../../GL/GLVertexBuffer.h"
#include "../../../GL/FONTS/GLFontManager.h"
#include "../../../GL/FONTS/GLFont.h"

namespace UI {
    namespace THEME {
        namespace DEFAULT {

            LabelView::LabelView()
            : ComponentView()
            , m_background(0)
            , m_backgroundColor(0)
            , m_text(0)
            , m_textColor(0)
            , m_texture(0)
            , m_fontHandle(0) {
            }

            LabelView::~LabelView() {
                if (m_background)
                    delete m_background;
                if (m_backgroundColor)
                    delete m_backgroundColor;
                if (m_text)
                    delete m_text;
                if (m_textColor)
                    delete m_textColor;
                if (m_texture)
                    delete m_texture;
                if (m_fontHandle)
                    delete m_fontHandle;
            }

            void LabelView::update(Component& component) {
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

                COMPONENTS::Label& label = static_cast<COMPONENTS::Label&> (component);
                if (m_text && m_textColor && m_texture && m_fontHandle) {
                    MATH::vec2 pen;
                    pen.x = 0;
                    pen.y = (*m_fontHandle)->getAscender();
                    m_text->setRenderBuffer((*m_fontHandle)->createText(label.getText(), pen));
                }
            }

            void LabelView::render(REND::Renderer& renderer, const Component& component) {
                const COMPONENTS::Label& label = static_cast<const COMPONENTS::Label&> (component);
                if (m_background && m_backgroundColor && label.hasBackground()) {
                    m_background->activateProgram(renderer);
                    m_backgroundColor->set(label.getBackgroundColor().data);
                    m_background->draw(renderer);
                }

                if (m_text && m_textColor && m_texture) {
                    int h = component.getHeight();
                    int w = component.getWidth();
                    
                    int pX = component.getHPadding();
                    int pY = component.getVPadding();

                    int shiftX;
                    int shiftY;

                    switch (label.getVTextAlign()) {
                        case COMPONENTS::Label::TOP:
                            shiftY =  1.0f * pY;
                            break;
                        case COMPONENTS::Label::BOTTOM:
                            shiftY = round(((float) h - m_textDimensions.y * 1.0f - 2.0f * pY));
                            break;
                        case COMPONENTS::Label::MIDDLE:
                            shiftY = round(((float) h - m_textDimensions.y * 1.5f) / 2.f);
                            break;
                    }

                    switch (label.getTextAlign()) {
                        case COMPONENTS::Label::LEFT:
                            shiftX =  1.0f * pY;
                            break;
                        case COMPONENTS::Label::RIGHT:
                            shiftX = round(((float) w - m_textDimensions.x -  2.0f * pX));
                            break;
                        case COMPONENTS::Label::CENTER:
                            shiftX = round(((float) w - m_textDimensions.x) / 2.f);
                            break;
                    }

                    renderer.PushMatrix();
                    renderer.Translate(shiftX, shiftY, 0);

                    m_text->activateProgram(renderer);

                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, static_cast<GL::FONTS::GLFont*> (m_fontHandle->operator *())->getTexture());
                    int t0 = 0;
                    m_texture->set(&t0);

                    m_textColor->set(label.getTextColor().data);

                    m_text->draw(renderer);
                    renderer.PopMatrix();
                }

            }

            ComponentView* LabelView::create(Component& cmp, Context& ctx) {
                COMPONENTS::Label& label = static_cast<COMPONENTS::Label&> (cmp);
                GL::GLShaderManager& shaderManager = static_cast<GL::GLShaderManager&> (ctx.getShaderManager());

                // create and fill the vertex buffer
                GL::GLVertexBuffer* backgroundBuffer = new GL::GLVertexBuffer("vertex:2f");
                GLuint indices[6] = {0, 1, 2, 0, 3, 1};
                MATH::vec2 vertices[4] = {
                    {0, 0},
                    {label.getWidth() - 2 * cmp.getHPadding(), label.getHeight() - 2 * cmp.getVPadding()},
                    {0, label.getHeight() - 2 * cmp.getVPadding()},
                    {label.getWidth() - 2 * cmp.getHPadding(), 0}
                };
                backgroundBuffer->push_back(vertices, 4, indices, 6);

                LabelView* labelView = new LabelView;
                labelView->m_background = new REND::Renderable(backgroundBuffer, ctx.getShaderManager().getShaderProgramInstance("flat"));
                labelView->m_backgroundColor = labelView->m_background->getShaderInstance().createUniformSetting("color", false);

                if (label.getText().size()) {
                    REND::FONTS::FontManager& fontManager = ctx.getFontManager();
                    REND::FONTS::FontDescription raleway("Raleway-Thin", 48);
                    SYS::Handle<REND::FONTS::Font>* fontHandle = fontManager.getFontPointer(raleway);
                    labelView->m_fontHandle = fontHandle;
                    MATH::vec2 pen;
                    pen.x = 0;
                    pen.y = (*fontHandle)->getAscender();
                    if (labelView->m_fontHandle) {
                        labelView->m_text = new REND::Renderable((*labelView->m_fontHandle)->createText(label.getText(), pen), ctx.getShaderManager().getShaderProgramInstance("TextShader"));
                        labelView->m_textColor = labelView->m_text->getShaderInstance().createUniformSetting("color", false);
                        labelView->m_texture = labelView->m_text->getShaderInstance().createUniformSetting("fonttexture", false);

                        label.setMinimumSize(pen.x + 2 * cmp.getHPadding(), pen.y + 2 * cmp.getVPadding());
                        labelView->m_textDimensions.x = pen.x;
                        labelView->m_textDimensions.y = pen.y;
                    }
                }

                return labelView;
            }
        }
    }
}
