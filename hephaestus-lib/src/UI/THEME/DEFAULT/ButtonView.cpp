/* 
 * File:   ButtonView.cpp
 * Author: chris
 * 
 * Created on June 11, 2014, 10:58 PM
 */

#include "ButtonView.h"
#include "../../Context.h"
#include "../../../REND/Renderable.h"
#include "../../../REND/UniformSetting.h"
#include "../../COMPONENTS/Button.h"

// OpenGL
#include "../../../GL/GLShaderManager.h"
#include "../../../GL/GLVertexBuffer.h"
#include "../../../GL/FONTS/GLFontManager.h"
#include "../../../GL/FONTS/GLFont.h"

namespace UI {
    namespace THEME {
        namespace DEFAULT {

            ButtonView::ButtonView()
            : ComponentView()
            , m_background(0)
            , m_backgroundColor(0)
            , m_text(0)
            , m_textColor(0)
            , m_texture(0)
            , m_fontHandle(0) {
            }

            ButtonView::~ButtonView() {
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

            void ButtonView::update(Component& component) {
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

                COMPONENTS::Button& button = static_cast<COMPONENTS::Button&> (component);
                if (m_text && m_textColor && m_texture && m_fontHandle) {
                    MATH::vec2 pen;
                    pen.x = 0;
                    pen.y = (*m_fontHandle)->getAscender();
                    m_text->setRenderBuffer((*m_fontHandle)->createText(button.getText(), pen));
                }
            }

            void ButtonView::render(REND::Renderer& renderer, const Component& component) {
                const COMPONENTS::Button& button = static_cast<const COMPONENTS::Button&> (component);
                if (m_background && m_backgroundColor) {
                    m_background->activateProgram(renderer);
                    m_backgroundColor->set(button.getBackgroundColor().data);
                    m_background->draw(renderer);
                }

                if (m_text && m_textColor && m_texture) {
                    int h = component.getHeight();
                    int w = component.getWidth();

                    int shiftX;
                    int shiftY;

                    switch (button.getVTextAlign()) {
                        case COMPONENTS::Button::TOP:
                            shiftY = 0;
                            break;
                        case COMPONENTS::Button::BOTTOM:
                            shiftY = round(((float) h - m_textDimensions.y * 1.0f));
                            break;
                        case COMPONENTS::Button::MIDDLE:
                            shiftY = round(((float) h - m_textDimensions.y * 1.5f) / 2.f);
                            break;
                    }

                    switch (button.getTextAlign()) {
                        case COMPONENTS::Button::LEFT:
                            shiftX = 0;
                            break;
                        case COMPONENTS::Button::RIGHT:
                            shiftX = round(((float) w - m_textDimensions.x));
                            break;
                        case COMPONENTS::Button::CENTER:
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

                    m_textColor->set(button.getTextColor().data);

                    m_text->draw(renderer);
                    renderer.PopMatrix();
                }

            }

            ComponentView* ButtonView::create(Component& cmp, Context& ctx) {
                COMPONENTS::Button& button = static_cast<COMPONENTS::Button&> (cmp);
                GL::GLShaderManager& shaderManager = static_cast<GL::GLShaderManager&> (ctx.getShaderManager());

                // create and fill the vertex buffer
                GL::GLVertexBuffer* backgroundBuffer = new GL::GLVertexBuffer("vertex:2f");
                GLuint indices[6] = {0, 1, 2, 0, 3, 1};
                MATH::vec2 vertices[4] = {
                    {0, 0},
                    {button.getWidth() - 2 * cmp.getHPadding(), button.getHeight() - 2 * cmp.getVPadding()},
                    {0, button.getHeight() - 2 * cmp.getVPadding()},
                    {button.getWidth() - 2 * cmp.getHPadding(), 0}
                };
                backgroundBuffer->push_back(vertices, 4, indices, 6);

                ButtonView* buttonView = new ButtonView;
                buttonView->m_background = new REND::Renderable(backgroundBuffer, ctx.getShaderManager().getShaderProgramInstance("flat"));
                buttonView->m_backgroundColor = buttonView->m_background->getShaderInstance().createUniformSetting("color", false);

                if (button.getText().size()) {
                    REND::FONTS::FontManager& fontManager = ctx.getFontManager();
                    REND::FONTS::FontDescription raleway("Raleway-Thin", 48);
                    SYS::Handle<REND::FONTS::Font>* fontHandle = fontManager.getFontPointer(raleway);
                    buttonView->m_fontHandle = fontHandle;
                    MATH::vec2 pen;
                    pen.x = 0;
                    pen.y = (*fontHandle)->getAscender();
                    if (buttonView->m_fontHandle) {
                        buttonView->m_text = new REND::Renderable((*buttonView->m_fontHandle)->createText(button.getText(), pen), ctx.getShaderManager().getShaderProgramInstance("TextShader"));
                        buttonView->m_textColor = buttonView->m_text->getShaderInstance().createUniformSetting("color", false);
                        buttonView->m_texture = buttonView->m_text->getShaderInstance().createUniformSetting("fonttexture", false);

                        button.setMinimumSize(pen.x + 2 * cmp.getHPadding(), pen.y + 2 * cmp.getVPadding());
                        buttonView->m_textDimensions.x = pen.x;
                        buttonView->m_textDimensions.y = pen.y;
                    }
                }

                return buttonView;
            }
        }
    }
}
