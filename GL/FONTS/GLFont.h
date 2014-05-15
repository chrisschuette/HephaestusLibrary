/* 
 * File:   GLFont.h
 * Author: chris
 *
 * Created on February 13, 2014, 3:05 PM
 */

#ifndef GLFONT_H
#define	GLFONT_H

#include "../../REND/FONTS/Font.h"
#include "../../LOG/Source.h"
#include "GLGlyph.h"

#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace GL {
    class GLTextureAtlas;
    namespace FONTS {
        namespace GLFont_CONST {
            const int HRES = 64;
            const int DPI = 72;
            const float HRESf = 64.f;
        }
        class GLFont: public REND::FONTS::Font, public LOG::Source {
        public:
            GLFont(MEM::Pool<SYS::Reference<Font> >& referencePool,
                    std::string fontName, unsigned int fontSize,
                    std::string filename, GL::GLTextureAtlas& atlas);
            GLFont(MEM::Pool<SYS::Reference<Font> >& referencePool,
                    const REND::FONTS::FontDescription& description,
                    std::string filename, GL::GLTextureAtlas& atlas);
            virtual ~GLFont();
            
            size_t load_glyphs(const wchar_t * charcodes);
            GLGlyph* get_glyph(wchar_t charcode);
            unsigned int  getTexture() const;
            
            
            virtual float getAscender() const { return m_ascender; }
            virtual float getDescender() const { return m_descender; }
            virtual float getLineGap() const { return m_linegap; }
            virtual float getLineHeight() const { return m_height; }
            
        private:
            void init();
            int get_face_with_size(float size, FT_Library *library, FT_Face *face);
            int get_face(FT_Library *library, FT_Face *face);
            int get_hires_face(FT_Library *library, FT_Face *face);
            int load_face(float size, FT_Library *library, FT_Face *face);
            void generate_kerning();
            GL::GLTextureAtlas& m_textureAtlas;
            std::string m_filename;
            std::vector<GLGlyph> m_glyphs;
                  
            int m_hinting;
            int m_outline_type;
            float m_outline_thickness;
            int m_filtering;
            int m_kerning;
            unsigned char m_lcd_weights[5];
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
            float m_underline_position;
            float m_underline_thickness;
        };
    }
}
#endif	/* GLFONT_H */

