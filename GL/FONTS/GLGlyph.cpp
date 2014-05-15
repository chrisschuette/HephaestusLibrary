/* 
 * File:   GLGlyph.cpp
 * Author: chris
 * 
 * Created on February 13, 2014, 2:56 PM
 */

#include "GLGlyph.h"

namespace GL {
    namespace FONTS {

        GLGlyph::GLGlyph() {
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
        }

        GLGlyph::~GLGlyph() {
        }

        float GLGlyph::getKerning(const wchar_t charcode) {
            size_t i;

            for (i = 0; i < kerning.size(); ++i) {
                const GLGlyphKerning & k = kerning.at(i);
                if (k.charcode == charcode) {
                    return k.kerning;
                }
            }
            return 0;
        }
    }
}
