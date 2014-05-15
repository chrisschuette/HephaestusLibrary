/* 
 * File:   ButtonView.cpp
 * Author: chris
 * 
 * Created on February 10, 2014, 12:31 AM
 */

#include "ButtonView.h"
#include "../../COMPONENTS/Button.h"
#include "../../Component.h"
#include "../../Context.h"
#include "../../../REND/ShaderManager.h"
#include "../../../GL/GLShaderProgram.h"
#include "../../../MATH/vec234.h"
#include "../../../GL/GUIRenderer.h"
#include "../../../GL/FONTS/GLFont.h"
#include "../../../GL/FONTS/GLFontManager.h"

// FONTS
#include "../../../REND/FONTS/FontDescription.h"
#include "../../../REND/FONTS/FontManager.h"
#include <iostream>

namespace GUI {
    namespace THEMES {
        namespace DEFAULT {

            ButtonView::ButtonView()
            : ComponentView()
            , LOG::Source("Buttonview")
            , m_outline(0)
            , m_captionText(0)
            , m_shaderProgram(0)
            , m_outlineProgram(0)
            , m_fontHandle(0) {

            }

            ButtonView::~ButtonView() {
                if (m_outline)
                    delete m_outline;
                if (m_captionText)
                    delete m_captionText;
                if (m_fontHandle)
                    delete m_fontHandle;
            }

            ComponentView* ButtonView::create(Component& cmp, Context& ctx) {

                GUI::COMPONENTS::Button& button = static_cast<GUI::COMPONENTS::Button&> (cmp);

                Renderer& renderer = ctx.getRenderer();
                REND::ShaderManager& shaderManager = renderer.getShaderManager();
                REND::FONTS::FontManager& fontManager = renderer.getFontManager();

                ButtonView* buttonView = new ButtonView;

                const GL::GLShaderProgram* shaderProgram = static_cast<const GL::GLShaderProgram*> (shaderManager.getShaderProgram("TextShader"));
                buttonView->m_shaderProgram = shaderProgram;

                buttonView->m_outlineProgram = static_cast<const GL::GLShaderProgram*> (shaderManager.getShaderProgram("flat"));

                REND::FONTS::FontDescription arialMedium("SketchGothicSchool", 50);
                SYS::Handle<REND::FONTS::Font>* fontHandle = fontManager.getFontPointer(arialMedium);
                buttonView->m_fontHandle = fontHandle;

                REND::FONTS::Font* font = fontHandle->operator *();

                MATH::vec2 pen;
                pen.x = 0;
                pen.y = font->getAscender();

                if (buttonView->m_fontHandle) {
                    buttonView->m_captionText = static_cast<GL::FONTS::GLFontManager&> (fontManager).createText(button.getButtonText(), *buttonView->m_fontHandle, &pen);
                    L_SENDER(normal, "Buttonview") << "captionText size: " << pen.x << " x " << pen.y;
                }

                GL::GLVertexBuffer* outline = new GL::GLVertexBuffer("vertex:2f,tex_coord:2f");
                GLuint indices[6] = {0, 1, 2, 0, 3, 1};
                MATH::vec4 vertices[4] = {
                    {0, 0, 0, 0},
                    {pen.x, font->getLineHeight(), 1, 1},
                    {0, font->getLineHeight(), 0, 1},
                    {pen.x, 0, 1, 0}
                };
                outline->push_back(vertices, 4, indices, 6);
                buttonView->m_outline = outline;

                // Font
                // - retrieve FontDescription
                // - get reference to FontManager from Renderer
                // - ask FontManager for FontDescription
                // - retrieve GLTextureFont
                // - fill VertexBuffer with Glyph coordinates
                // - save TextureAtlas ID
                // - calculate size

                // inform component of its size (important for layouting)
                cmp.setWidth(pen.x);
                cmp.setHeight(font->getLineHeight());

                return buttonView;
            }

            void ButtonView::render(const Component& component, VIEW::Context& context) {
                GUI::Context& ctx = static_cast<GUI::Context&> (context);
                GL::GUIRenderer& renderer = static_cast<GL::GUIRenderer&> (ctx.getRenderer());
                //renderer.debugTexture(*m_shaderProgram, static_cast<GL::FONTS::GLFont*>(m_fontHandle->operator *())->getTexture());

                if (component.getID().isValid())
                    glStencilFunc(GL_ALWAYS, component.getID(), -1);

                if (m_outlineProgram && m_outline) {
                    m_outlineProgram->activate();
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    m_outlineProgram->setUniformf("color", 0.8, 0.8, 0.8, 1.0);
                    m_outlineProgram->setUniform("projection", renderer.GetProjectionMatrix());
                    m_outlineProgram->setUniform("model", renderer.GetModelMatrix());
                    m_outline->render(GL_TRIANGLES);
                }

                if (m_shaderProgram && m_captionText) {
                    m_shaderProgram->activate();
                    m_shaderProgram->setUniformf("color", 0.5, 0.5, 1.0, 1.0);
                    m_shaderProgram->setUniform("projection", renderer.GetProjectionMatrix());
                    m_shaderProgram->setUniform("model", renderer.GetModelMatrix());
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, static_cast<GL::FONTS::GLFont*> (m_fontHandle->operator *())->getTexture());
                    m_shaderProgram->setUniformi("texture", 0);
                    m_captionText->render(GL_TRIANGLES);
                }
            }

        }
    }
}
