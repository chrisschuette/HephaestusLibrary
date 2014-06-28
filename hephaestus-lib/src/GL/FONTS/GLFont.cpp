/* 
 * File:   GLFont.cpp
 * Author: chris
 * 
 * Created on February 13, 2014, 3:05 PM
 */

#include "GLFont.h"
#include "../GLTextureAtlas.h"
#include "../../LOG/Core.h"
#include "../GLVertexBuffer.h"

// freetype2
#include FT_STROKER_H
#include FT_LCD_FILTER_H

#include <assert.h>
#include "FTERRORS.h"

#define NAME "GLFont"

namespace GL {
    namespace FONTS {

        GLFont::GLFont(MEM::Pool<SYS::Reference<Font> >& referencePool,
                std::string fontName, unsigned int fontSize,
                std::string filename, GL::GLTextureAtlas& atlas)
        : REND::FONTS::Font(referencePool, REND::FONTS::FontDescription(fontName, fontSize))
        , m_textureAtlas(atlas)
        , m_filename(filename) {
            init();
        }

        GLFont::GLFont(MEM::Pool<SYS::Reference<Font> >& referencePool,
                const REND::FONTS::FontDescription& description,
                std::string filename, GL::GLTextureAtlas& atlas)
        : REND::FONTS::Font(referencePool, description)
        , m_textureAtlas(atlas)
        , m_filename(filename) {
            init();
        }

        void GLFont::init() {
            FT_Library library;
            FT_Face face;
            FT_Size_Metrics metrics;

            assert(m_fontDescription.getFontSize() > 0);

            m_height = 0;
            m_ascender = 0;
            m_descender = 0;
            m_outline_type = 0;
            m_outline_thickness = 0.0;
            m_hinting = 1;
            m_kerning = 1;
            m_filtering = 1;

            // FT_LCD_FILTER_LIGHT   is (0x00, 0x55, 0x56, 0x55, 0x00)
            // FT_LCD_FILTER_DEFAULT is (0x10, 0x40, 0x70, 0x40, 0x10)
            m_lcd_weights[0] = 0x10;
            m_lcd_weights[1] = 0x40;
            m_lcd_weights[2] = 0x70;
            m_lcd_weights[3] = 0x40;
            m_lcd_weights[4] = 0x10;

            /* Get font metrics at high resolution */
            if (!get_hires_face(&library, &face))
                return;

            m_underline_position = face->underline_position / (float) (GLFont_CONST::HRESf * GLFont_CONST::HRESf) * (float) m_fontDescription.getFontSize();
            m_underline_position = round(m_underline_position);
            if (m_underline_position > -2) {
                m_underline_position = -2.0;
            }

            m_underline_thickness = face->underline_thickness / (float) (GLFont_CONST::HRESf * GLFont_CONST::HRESf) * (float) m_fontDescription.getFontSize();
            m_underline_thickness = round(m_underline_thickness);
            if (m_underline_thickness < 1) {
                m_underline_thickness = 1.0;
            }

            metrics = face->size->metrics;
            m_ascender = (metrics.ascender >> 6) / 100.0;
            m_descender = (metrics.descender >> 6) / 100.0;
            m_height = (metrics.height >> 6) / 100.0;
            L(normal) << "font height: " << m_height;
            m_linegap = m_height - m_ascender + m_descender;
            FT_Done_Face(face);
            FT_Done_FreeType(library);

            /* -1 is a special glyph */
            GLGlyph * glyph = get_glyph(-1);
            delete glyph;
        }

        unsigned int GLFont::getTexture() const {
            return m_textureAtlas.getTexture();
        }

        GLGlyph* GLFont::get_glyph(wchar_t charcode) {
            size_t i;
            wchar_t buffer[2] = {0, 0};
            GLGlyph *glyph = 0;

            assert(m_filename.size() > 0);

            /* Check if charcode has been already loaded */
            for (i = 0; i < m_glyphs.size(); ++i) {
                glyph = &m_glyphs.at(i);
                // If charcode is -1, we don't care about outline type or thickness
                if ((glyph->charcode == charcode) &&
                        ((charcode == (wchar_t)(-1)) ||
                        ((glyph->outline_type == m_outline_type) &&
                        (glyph->outline_thickness == m_outline_thickness)))) {
                    return glyph;
                }
            }

            /* charcode -1 is special : it is used for line drawing (overline,
             * underline, strikethrough) and background.
             */
            if (charcode == (wchar_t)(-1)) {
                size_t width = m_textureAtlas.getWidth();
                size_t height = m_textureAtlas.getHeight();
                MATH::ivec4 region = m_textureAtlas.get_region(5, 5);
                GLGlyph * glyph = new GLGlyph;
                static unsigned char data[4 * 4 * 3] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
                if (region.x < 0) {
                    fprintf(stderr, "Texture atlas is full (line %d)\n", __LINE__);
                    return NULL;
                }
                m_textureAtlas.set_region(region.x, region.y, 4, 4, data, 0);
                glyph->charcode = (wchar_t)(-1);
                glyph->s0 = (region.x + 2) / (float) width;
                glyph->t0 = (region.y + 2) / (float) height;
                glyph->s1 = (region.x + 3) / (float) width;
                glyph->t1 = (region.y + 3) / (float) height;
                m_glyphs.push_back(*glyph);
                return glyph; //*(texture_glyph_t **) vector_back( m_glyphs );
            }

            /* Glyph has not been already loaded */
            buffer[0] = charcode;
            if (load_glyphs(buffer) == 0) {
                return &m_glyphs.back();
            }
            return NULL;
        }

        int GLFont::get_face_with_size(float size,
                FT_Library *library, FT_Face * face) {
            return load_face(size, library, face);
        }

        int GLFont::get_face(FT_Library *library, FT_Face * face) {
            return get_face_with_size(m_fontDescription.getFontSize(), library, face);
        }

        int GLFont::get_hires_face(FT_Library *library, FT_Face * face) {
            return get_face_with_size(
                    ((float) m_fontDescription.getFontSize()) * 100.f, library, face);
        }

        int GLFont::load_face(float size,
                FT_Library *library, FT_Face * face) {
            FT_Error error;
            FT_Matrix matrix = {
                (int) ((1.0 / GLFont_CONST::HRES) * 0x10000L),
                (int) ((0.0) * 0x10000L),
                (int) ((0.0) * 0x10000L),
                (int) ((1.0) * 0x10000L)
            };

            assert(library);
            assert(size);

            /* Initialize library */
            error = FT_Init_FreeType(library);
            if (error) {
                L(warning) << "FT_Error (" << FT_Errors[error].code << ") : " << FT_Errors[error].message;
                return 0;
            }

            error = FT_New_Face(*library, m_filename.c_str(), 0, face);


            if (error) {
                L(warning) << "FT_Error (" << FT_Errors[error].code << ") : " << FT_Errors[error].message;
                FT_Done_FreeType(*library);
                return 0;
            }

            /* Select charmap */
            error = FT_Select_Charmap(*face, FT_ENCODING_UNICODE);
            if (error) {
                L(warning) << "FT_Error (" << FT_Errors[error].code << ") : " << FT_Errors[error].message;
                FT_Done_Face(*face);
                FT_Done_FreeType(*library);
                return 0;
            }

            /* Set char size */
            error = FT_Set_Char_Size(*face, (int) (size * GLFont_CONST::HRES), 0, GLFont_CONST::DPI * GLFont_CONST::HRES, GLFont_CONST::DPI);

            if (error) {
                L(warning) << "FT_Error (" << FT_Errors[error].code << ") : " << FT_Errors[error].message;
                FT_Done_Face(*face);
                FT_Done_FreeType(*library);
                return 0;
            }

            /* Set transform matrix */
            FT_Set_Transform(*face, &matrix, NULL);

            return 1;
        }

        size_t GLFont::load_glyphs(const wchar_t * charcodes) {
            size_t i, j, x, y, width, height, depth, w, h;
            FT_Library library;
            FT_Error error;
            FT_Face face;
            FT_Glyph ft_glyph;
            FT_GlyphSlot slot;
            FT_Bitmap ft_bitmap;

            FT_UInt glyph_index;
            MATH::ivec4 region;
            size_t missed = 0;

            assert(charcodes);


            width = m_textureAtlas.getWidth();
            height = m_textureAtlas.getHeight();
            depth = m_textureAtlas.getDepth();

            char pass;

            if (!get_face(&library, &face))
                return wcslen(charcodes);

            /* Load each glyph */
            for (i = 0; i < wcslen(charcodes); ++i) {
                pass = 0;
                /* Check if charcode has been already loaded */
                for (j = 0; j < m_glyphs.size(); ++j) {
                    GLGlyph& glyph = m_glyphs.at(j);
                    // If charcode is -1, we don't care about outline type or thickness
                    if ((glyph.charcode == charcodes[i])) {
                        pass = 1;
                        break;
                    }
                }

                if (pass)
                    continue; // don't add the item

                FT_Int32 flags = 0;
                int ft_glyph_top = 0;
                int ft_glyph_left = 0;
                glyph_index = FT_Get_Char_Index(face, charcodes[i]);
                // WARNING: We use texture-atlas depth to guess if user wants
                //          LCD subpixel rendering

                if (m_outline_type > 0) {
                    flags |= FT_LOAD_NO_BITMAP;
                } else {
                    flags |= FT_LOAD_RENDER;
                }

                if (!m_hinting) {
                    flags |= FT_LOAD_NO_HINTING | FT_LOAD_NO_AUTOHINT;
                } else {
                    flags |= FT_LOAD_FORCE_AUTOHINT;
                }


                if (depth == 3) {
                    FT_Library_SetLcdFilter(library, FT_LCD_FILTER_LIGHT);
                    flags |= FT_LOAD_TARGET_LCD;
                    if (m_filtering) {
                        FT_Library_SetLcdFilterWeights(library, m_lcd_weights);
                    }
                }
                error = FT_Load_Glyph(face, glyph_index, flags);
                if (error) {
                    L(warning) << "FT_Error (" << FT_Errors[error].code << ") : " << FT_Errors[error].message;
                    FT_Done_Face(face);
                    FT_Done_FreeType(library);
                    return wcslen(charcodes) - i;
                }


                if (m_outline_type == 0) {
                    slot = face->glyph;
                    ft_bitmap = slot->bitmap;
                    ft_glyph_top = slot->bitmap_top;
                    ft_glyph_left = slot->bitmap_left;
                } else {
                    FT_Stroker stroker;
                    FT_BitmapGlyph ft_bitmap_glyph;
                    error = FT_Stroker_New(library, &stroker);
                    if (error) {
                        L(warning) << "FT_Error (" << FT_Errors[error].code << ") : " << FT_Errors[error].message;
                        FT_Done_Face(face);
                        FT_Stroker_Done(stroker);
                        FT_Done_FreeType(library);
                        return 0;
                    }
                    FT_Stroker_Set(stroker,
                            (int) (m_outline_thickness * GLFont_CONST::HRES),
                            FT_STROKER_LINECAP_ROUND,
                            FT_STROKER_LINEJOIN_ROUND,
                            0);
                    error = FT_Get_Glyph(face->glyph, &ft_glyph);
                    if (error) {
                        L(warning) << "FT_Error (" << FT_Errors[error].code << ") : " << FT_Errors[error].message;

                        FT_Done_Face(face);
                        FT_Stroker_Done(stroker);
                        FT_Done_FreeType(library);
                        return 0;
                    }

                    if (m_outline_type == 1) {
                        error = FT_Glyph_Stroke(&ft_glyph, stroker, 1);
                    } else if (m_outline_type == 2) {
                        error = FT_Glyph_StrokeBorder(&ft_glyph, stroker, 0, 1);
                    } else if (m_outline_type == 3) {
                        error = FT_Glyph_StrokeBorder(&ft_glyph, stroker, 1, 1);
                    }
                    if (error) {
                        L(warning) << "FT_Error (" << FT_Errors[error].code << ") : " << FT_Errors[error].message;

                        FT_Done_Face(face);
                        FT_Stroker_Done(stroker);
                        FT_Done_FreeType(library);
                        return 0;
                    }

                    if (depth == 1) {
                        error = FT_Glyph_To_Bitmap(&ft_glyph, FT_RENDER_MODE_NORMAL, 0, 1);
                        if (error) {
                            L(warning) << "FT_Error (" << FT_Errors[error].code << ") : " << FT_Errors[error].message;

                            FT_Done_Face(face);
                            FT_Stroker_Done(stroker);
                            FT_Done_FreeType(library);
                            return 0;
                        }
                    } else {
                        error = FT_Glyph_To_Bitmap(&ft_glyph, FT_RENDER_MODE_LCD, 0, 1);
                        if (error) {
                            L(warning) << "FT_Error (" << FT_Errors[error].code << ") : " << FT_Errors[error].message;

                            FT_Done_Face(face);
                            FT_Stroker_Done(stroker);
                            FT_Done_FreeType(library);
                            return 0;
                        }
                    }
                    ft_bitmap_glyph = (FT_BitmapGlyph) ft_glyph;
                    ft_bitmap = ft_bitmap_glyph->bitmap;
                    ft_glyph_top = ft_bitmap_glyph->top;
                    ft_glyph_left = ft_bitmap_glyph->left;
                    FT_Stroker_Done(stroker);
                }


                // We want each glyph to be separated by at least one black pixel
                // (for example for shader used in demo-subpixel.c)
                w = ft_bitmap.width / depth + 1;
                h = ft_bitmap.rows + 1;
                region = m_textureAtlas.get_region(w, h);
                if (region.x < 0) {
                    missed++;
                    L(warning) << "Texture atlas is full.";
                    continue;
                }
                w = w - 1;
                h = h - 1;
                x = region.x;
                y = region.y;
                m_textureAtlas.set_region(x, y, w, h,
                        ft_bitmap.buffer, ft_bitmap.pitch);

                GLGlyph glyph;
                glyph.charcode = charcodes[i];
                glyph.width = w;
                glyph.height = h;
                glyph.outline_type = m_outline_type;
                glyph.outline_thickness = m_outline_thickness;
                glyph.offset_x = ft_glyph_left;
                glyph.offset_y = ft_glyph_top;
                glyph.s0 = x / (float) width;
                glyph.t0 = y / (float) height;
                glyph.s1 = (x + glyph.width) / (float) width;
                glyph.t1 = (y + glyph.height) / (float) height;

                // Discard hinting to get advance
                FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER | FT_LOAD_NO_HINTING);
                slot = face->glyph;
                glyph.advance_x = slot->advance.x / GLFont_CONST::HRESf;
                glyph.advance_y = slot->advance.y / GLFont_CONST::HRESf;

                m_glyphs.push_back(glyph);

                if (m_outline_type > 0) {
                    FT_Done_Glyph(ft_glyph);
                }
            }
            FT_Done_Face(face);
            FT_Done_FreeType(library);
            m_textureAtlas.upload();
            generate_kerning();
            return missed;
        }

        REND::RenderBuffer* GLFont::createText(std::string text, MATH::vec2& pen) {
            GLVertexBuffer* vertexBuffer = new GLVertexBuffer("vertex:2f,tex_coord:2f");
            size_t i;
            for (i = 0; i < text.size(); ++i) {
                GL::FONTS::GLGlyph * glyph = get_glyph(text.at(i));
                if (glyph != NULL) {
                    int kerning = 0;
                    if (i > 0) {
                        kerning = glyph->getKerning(text[i - 1]);
                    }
                    pen.x += kerning;
                    float x0 = (pen.x + glyph->offset_x);
                    float y0 = (pen.y - glyph->offset_y);
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
                    /*vertex_t vertices[4] = {
                        { x0, y0, s0, t0},
                        { x0, y1, s0, t1},
                        { x1, y1, s1, t1},
                        { x1, y0, s1, t0}
                    };*/
                    vertexBuffer->push_back(vertices, 4, indices, 6);
                    pen.x += glyph->advance_x;
                }
            }
            return vertexBuffer;
        }

        void GLFont::generate_kerning() {
            size_t i, j;
            FT_Library library;
            FT_Face face;
            FT_UInt glyph_index, prev_index;
            FT_Vector kerning;

            /* Load font */
            if (!get_face(&library, &face))
                return;

            /* For each glyph couple combination, check if kerning is necessary */
            /* Starts at index 1 since 0 is for the special backgroudn glyph */
            for (i = 1; i < m_glyphs.size(); ++i) {
                GLGlyph& glyph = m_glyphs.at(i);
                glyph_index = FT_Get_Char_Index(face, glyph.charcode);
                glyph.kerning.clear();

                for (j = 1; j < m_glyphs.size(); ++j) {
                    GLGlyph& prev_glyph = m_glyphs.at(j);
                    prev_index = FT_Get_Char_Index(face, prev_glyph.charcode);
                    FT_Get_Kerning(face, prev_index, glyph_index, FT_KERNING_UNFITTED, &kerning);
                    // printf("%c(%d)-%c(%d): %ld\n",
                    //       prev_glyph->charcode, prev_glyph->charcode,
                    //       glyph_index, glyph_index, kerning.x);
                    if (kerning.x) {
                        GLGlyph::GLGlyphKerning k;
                        k.charcode = prev_glyph.charcode;
                        k.kerning = kerning.x / (float) (GLFont_CONST::HRESf * GLFont_CONST::HRESf);
                        glyph.kerning.push_back(k);
                    }
                }
            }

            FT_Done_Face(face);
            FT_Done_FreeType(library);
        }

        GLFont::~GLFont() {
        }
    }
}
