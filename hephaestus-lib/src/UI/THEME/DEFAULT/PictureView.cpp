/* 
 * File:   PictureView.cpp
 * Author: chris
 * 
 * Created on June 12, 2014, 12:20 PM
 */

#include "PictureView.h"
#include "../../COMPONENTS/Picture.h"
#include "../../../LOG/Core.h"
#include "../../Context.h"

#include "../../../REND/Renderable.h"
#include "../../../REND/UniformSetting.h"
#include "../../../GL/GLVertexBuffer.h"
#include "../../../GL/GLTexture.h"

#define NAME "PictureView"

namespace UI {
    namespace THEME {
        namespace DEFAULT {

            PictureView::PictureView() : ComponentView(), m_background(0)
            , m_backgroundColor(0), m_sprite(0), m_picture(0), m_textureHandle(0) {
            }

            PictureView::~PictureView() {
                if (m_background)
                    delete m_background;
                if (m_backgroundColor)
                    delete m_backgroundColor;
                if (m_sprite)
                    delete m_sprite;
                if (m_picture)
                    delete m_picture;
                if (m_textureHandle)
                    delete m_textureHandle;
            }

            void PictureView::update(Component& component) {
                /*if (m_background && m_background->getRenderBuffer()) {
                    GL::GLVertexBuffer* vb = static_cast<GL::GLVertexBuffer*> (m_background->getRenderBuffer());
                    int x = component.getWidth();
                    int y = component.getHeight();
                    L(normal) << x << " " << y;
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
                }*/
            }

            void PictureView::render(REND::Renderer& renderer, const Component& component) {
                const COMPONENTS::Picture& picture = static_cast<const COMPONENTS::Picture&> (component);
                if (m_background && m_backgroundColor) {
                    m_background->activateProgram(renderer);
                    MATH::vec4 color;
                    color.r = 1;
                    color.g = 0;
                    color.b = 0;
                    color.a = 1;
                    m_backgroundColor->set(color.data);
                    m_background->draw(renderer);
                }
                if (m_picture && m_sprite) {

                    m_picture->activateProgram(renderer);

                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, static_cast<GL::GLTexture*> ((*m_textureHandle).get())->getTextureName());
                    int t0 = 0;
                    m_sprite->set(&t0);

                    m_picture->draw(renderer);
                }
            }

            ComponentView* PictureView::create(Component& cmp, Context& ctx) {
                COMPONENTS::Picture& picture = static_cast<COMPONENTS::Picture&> (cmp);
                PictureView* pictureView = new PictureView;

                SYS::Handle<REND::Texture> textureHandle = ctx.getTextureManager().getResourceHandle("title");
                int W = textureHandle->getTextureWidth();
                int H = textureHandle->getTextureHeight();
                pictureView->m_textureHandle = new SYS::Handle<REND::Texture>(textureHandle);
                GLuint indices[6] = {0, 1, 2, 0, 3, 1};

                /*
                // create and fill the vertex buffer
                GL::GLVertexBuffer* backgroundBuffer = new GL::GLVertexBuffer("vertex:2f");
                MATH::vec2 vertices[4] = {
                    {0, 0},
                    {W - 2 * cmp.getHPadding(), H - 2 * cmp.getVPadding()},
                    {0, H - 2 * cmp.getVPadding()},
                    {W - 2 * cmp.getHPadding(), 0}
                };
                backgroundBuffer->push_back(vertices, 4, indices, 6);

                pictureView->m_background = new REND::Renderable(backgroundBuffer, ctx.getShaderManager().getShaderProgramInstance("flat"));
                pictureView->m_backgroundColor = pictureView->m_background->getShaderInstance().createUniformSetting("color", false);
                 */
                // create and fill the vertex buffer
                GL::GLVertexBuffer* buffer = new GL::GLVertexBuffer("vertex:2f,tex_coord:2f");
                MATH::vec4 vertices2[4] = {
                    {0, 0, 0, 0},
                    {W - 2 * cmp.getHPadding(), H - 2 * cmp.getVPadding(), 1, 1},
                    {0, H - 2 * cmp.getVPadding(), 0, 1},
                    {W - 2 * cmp.getHPadding(), 0, 1, 0}
                };
                buffer->push_back(vertices2, 4, indices, 6);


                pictureView->m_picture = new REND::Renderable(buffer, ctx.getShaderManager().getShaderProgramInstance("texture"));
                pictureView->m_sprite = pictureView->m_picture->getShaderInstance().createUniformSetting("sprite", false);

                picture.setMinimumSize(W, H);
                picture.setMaximumSize(W, H);
                picture.resize(W, H);

                return pictureView;
            }
        }
    }
}
