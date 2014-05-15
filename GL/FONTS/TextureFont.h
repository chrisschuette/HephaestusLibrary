/* 
 * File:   TextureFont.h
 * Author: chris
 *
 * Created on February 6, 2014, 8:48 PM
 */

#ifndef TEXTUREFONT_H
#define	TEXTUREFONT_H

#include "../../REND/FONTS/Font.h"

#include "../../MEM/Vector.h"
#include "../GLTextureAtlas.h"
#include "TextureGlyph.h"

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H
#include FT_LCD_FILTER_H

namespace GL {
    namespace FONTS {

        namespace TextureFont_CONST {
            const int HRES = 64;
            const int DPI = 72;
            const float HRESf = 64.f;
        }

        class TextureFont : public REND::FONTS::Font {
        public:
            TextureFont(MEM::Pool<SYS::Reference<Font> >& referencePool, 
                    std::string fontName, unsigned int size,
                    std::string filename, GL::GLTextureAtlas * atlas);
            TextureFont(const TextureFont& orig);
            virtual ~TextureFont();

            void init();
            int get_face_with_size(float size, FT_Library *library, FT_Face *face);
            int get_face(FT_Library *library, FT_Face *face);
            int get_hires_face(FT_Library *library, FT_Face *face);
            int load_face(float size, FT_Library *library, FT_Face *face);
            TextureGlyph * get_glyph(wchar_t charcode);
            size_t load_glyphs(const wchar_t * charcodes);
            void generate_kerning();

            float getHeight() const {
                return m_height;
            }
        private:
            /**
             * Vector of glyphs contained in this font.
             */
            MEM::Vector * m_glyphs;

            /**
             * Atlas structure to store glyphs data.
             */
            GL::GLTextureAtlas * m_atlas;

            /**
             * font location
             */
            enum {
                TEXTURE_FONT_FILE = 0,
                TEXTURE_FONT_MEMORY,
            } m_location;

            std::string m_filename;

            /**
             * Font memory address, for when location == TEXTURE_FONT_MEMORY
             */
            struct {
                const void *base;
                size_t size;
            } m_memory;

            /**
             * Font size
             */
            //float m_size;

            /**
             * Whether to use autohint when rendering font
             */
            int m_hinting;

            /**
             * Outline type (0 = None, 1 = line, 2 = inner, 3 = outer)
             */
            int m_outline_type;

            /**
             * Outline thickness
             */
            float m_outline_thickness;

            /** 
             * Whether to use our own lcd filter.
             */
            int m_filtering;

            /**
             * Whether to use kerning if available
             */
            int m_kerning;

            /**
             * LCD filter weights
             */
            unsigned char m_lcd_weights[5];

            /**
             * This field is simply used to compute a default line spacing (i.e., the
             * baseline-to-baseline distance) when writing text with this font. Note
             * that it usually is larger than the sum of the ascender and descender
             * taken as absolute values. There is also no guarantee that no glyphs
             * extend above or below subsequent baselines when using this distance.
             */
            float m_height;

            /**
             * This field is the distance that must be placed between two lines of
             * text. The baseline-to-baseline distance should be computed as:
             * ascender - descender + linegap
             */
            float m_linegap;

            /**
             * The ascender is the vertical distance from the horizontal baseline to
             * the highest 'character' coordinate in a font face. Unfortunately, font
             * formats define the ascender differently. For some, it represents the
             * ascent of all capital latin characters (without accents), for others it
             * is the ascent of the highest accented character, and finally, other
             * formats define it as being equal to bbox.yMax.
             */
            float m_ascender;

            /**
             * The descender is the vertical distance from the horizontal baseline to
             * the lowest 'character' coordinate in a font face. Unfortunately, font
             * formats define the descender differently. For some, it represents the
             * descent of all capital latin characters (without accents), for others it
             * is the ascent of the lowest accented character, and finally, other
             * formats define it as being equal to bbox.yMin. This field is negative
             * for values below the baseline.
             */
            float m_descender;

            /**
             * The position of the underline line for this face. It is the center of
             * the underlining stem. Only relevant for scalable formats.
             */
            float m_underline_position;

            /**
             * The thickness of the underline for this face. Only relevant for scalable
             * formats.
             */
            float m_underline_thickness;

        };
    }
}

#endif	/* TEXTUREFONT_H */

