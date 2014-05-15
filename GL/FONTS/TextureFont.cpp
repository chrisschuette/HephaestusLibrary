/* 
 * File:   TextureFont.cpp
 * Author: chris
 * 
 * Created on February 6, 2014, 8:48 PM
 */

#include "TextureFont.h"
#include "TextureGlyphKerning.h"
#include <assert.h>

#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       { 0, 0 } };

const struct {
    int code;
    const char* message;
} FT_Errors[] =
#include FT_ERRORS_H

        namespace GL {
    namespace FONTS {

        TextureFont::TextureFont(MEM::Pool<SYS::Reference<Font> >& referencePool, 
                std::string fontName, unsigned int size,
                    std::string filename, GL::GLTextureAtlas * atlas)
        : REND::FONTS::Font(referencePool, REND::FONTS::FontDescription(fontName, size))
        {

            m_atlas = atlas;

            m_location = TEXTURE_FONT_FILE;
            m_filename = filename;

            init();
        }

        TextureFont::~TextureFont() {
            size_t i;
            TextureGlyph *glyph;

            for (i = 0; i < m_glyphs->size(); ++i) {
                glyph = *(TextureGlyph **) m_glyphs->get(i);
                delete glyph;
            }

            delete m_glyphs;
        }

        void TextureFont::init() {
            FT_Library library;
            FT_Face face;
            FT_Size_Metrics metrics;

            assert(m_atlas);
            assert(m_fontDescription.getFontSize() > 0);
            assert((m_location == TEXTURE_FONT_FILE && (m_filename.size()>0))
                    || (m_location == TEXTURE_FONT_MEMORY
                    && m_memory.base && m_memory.size));

            m_glyphs = new MEM::Vector(sizeof (TextureGlyph *)); //vector_new(sizeof (texture_glyph_t *));
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

            m_underline_position = face->underline_position / (float) (TextureFont_CONST::HRESf * TextureFont_CONST::HRESf) * (float) m_fontDescription.getFontSize();
            m_underline_position = round(m_underline_position);
            if (m_underline_position > -2) {
                m_underline_position = -2.0;
            }

            m_underline_thickness = face->underline_thickness / (float) (TextureFont_CONST::HRESf * TextureFont_CONST::HRESf) * (float) m_fontDescription.getFontSize();
            m_underline_thickness = round(m_underline_thickness);
            if (m_underline_thickness < 1) {
                m_underline_thickness = 1.0;
            }

            metrics = face->size->metrics;
            m_ascender = (metrics.ascender >> 6) / 100.0;
            m_descender = (metrics.descender >> 6) / 100.0;
            m_height = (metrics.height >> 6) / 100.0;
            m_linegap = m_height - m_ascender + m_descender;
            FT_Done_Face(face);
            FT_Done_FreeType(library);

            /* -1 is a special glyph */
            get_glyph(-1);

        }

        int TextureFont::get_face_with_size(float size,
                FT_Library *library, FT_Face *face) {
            return load_face(size, library, face);
        }

        int TextureFont::get_face(FT_Library *library, FT_Face *face) {
            return get_face_with_size(m_fontDescription.getFontSize(), library, face);
        }

        int TextureFont::get_hires_face(FT_Library *library, FT_Face *face) {
            return get_face_with_size(
                    ((float) m_fontDescription.getFontSize()) * 100.f, library, face);
        }

        int TextureFont::load_face(float size,
                FT_Library *library, FT_Face *face) {
            FT_Error error;
            FT_Matrix matrix = {
                (int) ((1.0 / TextureFont_CONST::HRES) * 0x10000L),
                (int) ((0.0) * 0x10000L),
                (int) ((0.0) * 0x10000L),
                (int) ((1.0) * 0x10000L)
            };

            assert(library);
            assert(size);

            /* Initialize library */
            error = FT_Init_FreeType(library);
            if (error) {
                fprintf(stderr, "FT_Error (0x%02x) : %s\n",
                        FT_Errors[error].code, FT_Errors[error].message);
                return 0;
            }

            /* Load face */
            switch (m_location) {
                case TEXTURE_FONT_FILE:
                    error = FT_New_Face(*library, m_filename.c_str(), 0, face);
                    break;
                    /*
                                    case TEXTURE_FONT_MEMORY:
                                        error = FT_New_Memory_Face(*library,
                                                m_memory.base, m_memory.size, 0, face);
                                        break;
                     */
            }

            if (error) {
                fprintf(stderr, "FT_Error (line %d, code 0x%02x) : %s\n",
                        __LINE__, FT_Errors[error].code, FT_Errors[error].message);
                FT_Done_FreeType(*library);
                return 0;
            }

            /* Select charmap */
            error = FT_Select_Charmap(*face, FT_ENCODING_UNICODE);
            if (error) {
                fprintf(stderr, "FT_Error (line %d, code 0x%02x) : %s\n",
                        __LINE__, FT_Errors[error].code, FT_Errors[error].message);
                FT_Done_Face(*face);
                FT_Done_FreeType(*library);
                return 0;
            }

            /* Set char size */
            error = FT_Set_Char_Size(*face, (int) (size * TextureFont_CONST::HRES), 0, TextureFont_CONST::DPI * TextureFont_CONST::HRES, TextureFont_CONST::DPI);

            if (error) {
                fprintf(stderr, "FT_Error (line %d, code 0x%02x) : %s\n",
                        __LINE__, FT_Errors[error].code, FT_Errors[error].message);
                FT_Done_Face(*face);
                FT_Done_FreeType(*library);
                return 0;
            }

            /* Set transform matrix */
            FT_Set_Transform(*face, &matrix, NULL);

            return 1;
        }

        TextureGlyph * TextureFont::get_glyph(wchar_t charcode) {
            size_t i;
            wchar_t buffer[2] = {0, 0};
            TextureGlyph *glyph;

            assert(m_filename.size() > 0);
            assert(m_atlas);

            /* Check if charcode has been already loaded */
            for (i = 0; i < m_glyphs->size(); ++i) {
                glyph = *(TextureGlyph **) m_glyphs->get(i);
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
                size_t width = m_atlas->getWidth();
                size_t height = m_atlas->getHeight();
                MATH::ivec4 region = m_atlas->get_region(5, 5);
                TextureGlyph * glyph = new TextureGlyph;
                static unsigned char data[4 * 4 * 3] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
                if (region.x < 0) {
                    fprintf(stderr, "Texture atlas is full (line %d)\n", __LINE__);
                    return NULL;
                }
                m_atlas->set_region(region.x, region.y, 4, 4, data, 0);
                glyph->charcode = (wchar_t)(-1);
                glyph->s0 = (region.x + 2) / (float) width;
                glyph->t0 = (region.y + 2) / (float) height;
                glyph->s1 = (region.x + 3) / (float) width;
                glyph->t1 = (region.y + 3) / (float) height;
                m_glyphs->push_back(&glyph);
                return glyph; //*(texture_glyph_t **) vector_back( m_glyphs );
            }

            /* Glyph has not been already loaded */
            buffer[0] = charcode;
            if (load_glyphs(buffer) == 0) {
                return *(TextureGlyph **) m_glyphs->back();
            }
            return NULL;
        }

        size_t TextureFont::load_glyphs(const wchar_t * charcodes) {
            size_t i, j, x, y, width, height, depth, w, h;
            FT_Library library;
            FT_Error error;
            FT_Face face;
            FT_Glyph ft_glyph;
            FT_GlyphSlot slot;
            FT_Bitmap ft_bitmap;

            FT_UInt glyph_index;
            TextureGlyph *glyph;
            MATH::ivec4 region;
            size_t missed = 0;

            assert(charcodes);


            width = m_atlas->getWidth();
            height = m_atlas->getHeight();
            depth = m_atlas->getDepth();

            char pass;

            if (!get_face(&library, &face))
                return wcslen(charcodes);

            /* Load each glyph */
            for (i = 0; i < wcslen(charcodes); ++i) {
                pass = 0;
                /* Check if charcode has been already loaded */
                for (j = 0; j < m_glyphs->size(); ++j) {
                    glyph = *(TextureGlyph **) m_glyphs->get(j);
                    // If charcode is -1, we don't care about outline type or thickness
                    if ((glyph->charcode == charcodes[i])) {
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
                    fprintf(stderr, "FT_Error (line %d, code 0x%02x) : %s\n",
                            __LINE__, FT_Errors[error].code, FT_Errors[error].message);
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
                        fprintf(stderr, "FT_Error (0x%02x) : %s\n",
                                FT_Errors[error].code, FT_Errors[error].message);
                        FT_Done_Face(face);
                        FT_Stroker_Done(stroker);
                        FT_Done_FreeType(library);
                        return 0;
                    }
                    FT_Stroker_Set(stroker,
                            (int) (m_outline_thickness * TextureFont_CONST::HRES),
                            FT_STROKER_LINECAP_ROUND,
                            FT_STROKER_LINEJOIN_ROUND,
                            0);
                    error = FT_Get_Glyph(face->glyph, &ft_glyph);
                    if (error) {
                        fprintf(stderr, "FT_Error (0x%02x) : %s\n",
                                FT_Errors[error].code, FT_Errors[error].message);
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
                        fprintf(stderr, "FT_Error (0x%02x) : %s\n",
                                FT_Errors[error].code, FT_Errors[error].message);
                        FT_Done_Face(face);
                        FT_Stroker_Done(stroker);
                        FT_Done_FreeType(library);
                        return 0;
                    }

                    if (depth == 1) {
                        error = FT_Glyph_To_Bitmap(&ft_glyph, FT_RENDER_MODE_NORMAL, 0, 1);
                        if (error) {
                            fprintf(stderr, "FT_Error (0x%02x) : %s\n",
                                    FT_Errors[error].code, FT_Errors[error].message);
                            FT_Done_Face(face);
                            FT_Stroker_Done(stroker);
                            FT_Done_FreeType(library);
                            return 0;
                        }
                    } else {
                        error = FT_Glyph_To_Bitmap(&ft_glyph, FT_RENDER_MODE_LCD, 0, 1);
                        if (error) {
                            fprintf(stderr, "FT_Error (0x%02x) : %s\n",
                                    FT_Errors[error].code, FT_Errors[error].message);
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
                region = m_atlas->get_region(w, h);
                if (region.x < 0) {
                    missed++;
                    fprintf(stderr, "Texture atlas is full (line %d)\n", __LINE__);
                    continue;
                }
                w = w - 1;
                h = h - 1;
                x = region.x;
                y = region.y;
                m_atlas->set_region(x, y, w, h,
                        ft_bitmap.buffer, ft_bitmap.pitch);

                glyph = new TextureGlyph;
                glyph->charcode = charcodes[i];
                glyph->width = w;
                glyph->height = h;
                glyph->outline_type = m_outline_type;
                glyph->outline_thickness = m_outline_thickness;
                glyph->offset_x = ft_glyph_left;
                glyph->offset_y = ft_glyph_top;
                glyph->s0 = x / (float) width;
                glyph->t0 = y / (float) height;
                glyph->s1 = (x + glyph->width) / (float) width;
                glyph->t1 = (y + glyph->height) / (float) height;

                // Discard hinting to get advance
                FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER | FT_LOAD_NO_HINTING);
                slot = face->glyph;
                glyph->advance_x = slot->advance.x / TextureFont_CONST::HRESf;
                glyph->advance_y = slot->advance.y / TextureFont_CONST::HRESf;

                m_glyphs->push_back(&glyph);

                if (m_outline_type > 0) {
                    FT_Done_Glyph(ft_glyph);
                }
            }
            FT_Done_Face(face);
            FT_Done_FreeType(library);
            m_atlas->upload();
            generate_kerning();
            return missed;
        }

        void TextureFont::generate_kerning() {
            size_t i, j;
            FT_Library library;
            FT_Face face;
            FT_UInt glyph_index, prev_index;
            TextureGlyph *glyph, *prev_glyph;
            FT_Vector kerning;

            /* Load font */
            if (!get_face( &library, &face))
                return;

            /* For each glyph couple combination, check if kerning is necessary */
            /* Starts at index 1 since 0 is for the special backgroudn glyph */
            for (i = 1; i < m_glyphs->size(); ++i) {
                glyph = *(TextureGlyph **) m_glyphs->get(i);
                glyph_index = FT_Get_Char_Index(face, glyph->charcode);
                glyph->kerning->clear();

                for (j = 1; j < m_glyphs->size(); ++j) {
                    prev_glyph = *(TextureGlyph **) m_glyphs->get(j);
                    prev_index = FT_Get_Char_Index(face, prev_glyph->charcode);
                    FT_Get_Kerning(face, prev_index, glyph_index, FT_KERNING_UNFITTED, &kerning);
                    // printf("%c(%d)-%c(%d): %ld\n",
                    //       prev_glyph->charcode, prev_glyph->charcode,
                    //       glyph_index, glyph_index, kerning.x);
                    if (kerning.x) {
                        TextureGlyphKerning k;
                        k.charcode = prev_glyph->charcode;
                        k.kerning = kerning.x / (float) (TextureFont_CONST::HRESf * TextureFont_CONST::HRESf);
                        glyph->kerning->push_back(&k);
                    }
                }
            }

            FT_Done_Face(face);
            FT_Done_FreeType(library);
        }




    }
}
