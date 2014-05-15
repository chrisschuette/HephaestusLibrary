/* 
 * File:   TextureGlyph.cpp
 * Author: chris
 * 
 * Created on February 6, 2014, 10:39 PM
 */

#include "TextureGlyph.h"
#include "TextureGlyphKerning.h"

namespace GL {
    namespace FONTS {

        TextureGlyph::TextureGlyph() {
            id = 0;
            width = 0;
            height = 0;
            outline_type = 0;
            outline_thickness = 0.0;
            offset_x = 0;
            offset_y = 0;
            advance_x = 0.0;
            advance_y = 0.0;
            s0 = 0.0;
            t0 = 0.0;
            s1 = 0.0;
            t1 = 0.0;
            kerning = new MEM::Vector(sizeof (TextureGlyphKerning));
        }

        TextureGlyph::~TextureGlyph() {
            delete kerning;
        }

        float TextureGlyph::getKerning(const wchar_t charcode) {
            size_t i;

            for (i = 0; i < kerning->size(); ++i) {
                TextureGlyphKerning * k = (TextureGlyphKerning *) kerning->get(i);
                if (k->charcode == charcode) {
                    return k->kerning;
                }
            }
            return 0;
        }

    }
}
