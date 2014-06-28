/* 
 * File:   GLFontManager.cpp
 * Author: chris
 * 
 * Created on February 13, 2014, 3:58 PM
 */

#include "GLFontManager.h"
#include "GLFont.h"
#include "../GLVertexBuffer.h"
#include "../../MATH/vec234.h"

#define NAME "GLFontManager"

namespace GL {
    namespace FONTS {

        GLFontManager::GLFontManager()
        : REND::FONTS::FontManager()
        , m_textureAtlas(GLFontManager_CONST::TextureAtlasSize,
        GLFontManager_CONST::TextureAtlasSize, 1) {
        }

        GLFontManager::~GLFontManager() {
        }

        REND::FONTS::Font* GLFontManager::loadFont(const REND::FONTS::FontDescription& description) {
            // SUPER preliminary fontName => filename resolution:
            std::string filename = "fonts/" + description.getFontName() + ".ttf";

            // create the font
            GL::FONTS::GLFont* font = new GL::FONTS::GLFont(m_fontReferencePool,
                    description, filename, m_textureAtlas);

            const wchar_t *cache = L" !\"#$%&'()*+,-./0123456789:;<=>?"
                    L"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
                    L"`abcdefghijklmnopqrstuvwxyz{|}~";

            unsigned int missed = font->load_glyphs(cache);
            if (missed)
                L(error) << "Loading of " << missed << " glyphs for font " << description.getFontName() << " failed.";
            return font;
        }

        /*GLVertexBuffer* GLFontManager::createText(const std::string& text, SYS::Handle<REND::FONTS::Font>& fontHandle, MATH::vec2* pen) {
            GLFont* font = static_cast<GLFont*> (*fontHandle);
            GLVertexBuffer* vertexBuffer = new GLVertexBuffer("vertex:2f,tex_coord:2f");
            size_t i;
            for (i = 0; i < text.size(); ++i) {
                GL::FONTS::GLGlyph * glyph = font->get_glyph(text.at(i));
                if (glyph != NULL) {
                    int kerning = 0;
                    if (i > 0) {
                        kerning = glyph->getKerning(text[i - 1]);
                    }
                    pen->x += kerning;
                    float x0 = (pen->x + glyph->offset_x);
                    float y0 = (pen->y - glyph->offset_y);
                    float x1 = (x0 + glyph->width);
                    float y1 = (y0 + glyph->height);
                    float s0 = glyph->s0;
                    float t0 = glyph->t0;
                    float s1 = glyph->s1;
                    float t1 = glyph->t1;
                    GLuint indices[6] = {0, 1, 2, 0, 2, 3};
                    
                   // L(normal) << s0 << " X " << t0;
                   // L(normal) << s1 << " X " << t1;

                    typedef struct {
                        float x, y, u, v;
                    } vertex_t;
                    vertex_t vertices[4] = {
                        { x0, y0, s0, t0},
                        { x0, y1, s0, t1},
                        { x1, y1, s1, t1},
                        { x1, y0, s1, t0}
                    };

                    vertexBuffer->push_back(vertices, 4, indices, 6);
                    pen->x += glyph->advance_x;
                }
            }
            return vertexBuffer;
        }*/
        
        /*
        GLVertexBuffer* GLFontManager::createText(std::string text, SYS::Handle<REND::FONTS::Font>& fontHandle, MATH::vec2* pen) {
            GLFont* font = static_cast<GLFont*> (*fontHandle);
            GLVertexBuffer* vertexBuffer = new GLVertexBuffer("vertex:2f,tex_coord:2f");
            size_t i;
            for (i = 0; i < text.size(); ++i) {
                GL::FONTS::GLGlyph * glyph = font->get_glyph(text.at(i));
                if (glyph != NULL) {
                    int kerning = 0;
                    if (i > 0) {
                        kerning = glyph->getKerning(text[i - 1]);
                    }
                    pen->x += kerning;
                    float x0 = (pen->x + glyph->offset_x);
                    float y0 = (pen->y + glyph->offset_y);
                    float x1 = (x0 + glyph->width);
                    float y1 = (y0 - glyph->height);
                    float s0 = glyph->s0;
                    float t0 = glyph->t0;
                    float s1 = glyph->s1;
                    float t1 = glyph->t1;
                    GLuint indices[6] = {0, 1, 2, 0, 2, 3};
                    
                    L(normal) << s0 << " X " << t0;
                    L(normal) << s1 << " X " << t1;

                    typedef struct {
                        float x, y, u, v;
                    } vertex_t;
                    vertex_t vertices[4] = {
                        { x0, y0, s0, t0},
                        { x0, y1, s0, t1},
                        { x1, y1, s1, t1},
                        { x1, y0, s1, t0}
                    };
                    vertexBuffer->push_back(vertices, 4, indices, 6);
                    pen->x += glyph->advance_x;
                }
            }
            pen->y += font->getHeight();
            L(normal) << "Font height: " << font->getHeight();
            return vertexBuffer;
        }*/

    }
}
