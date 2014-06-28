/* 
 * File:   GLGlyph.h
 * Author: chris
 *
 * Created on February 13, 2014, 2:56 PM
 */

#ifndef GLGLYPH_H
#define	GLGLYPH_H

#include <stddef.h>
#include <vector>

namespace GL {
    namespace FONTS {
        struct GLGlyph {
            struct GLGlyphKerning {
                    wchar_t charcode;
                    float kerning;
            };

            GLGlyph();
            virtual ~GLGlyph();
            float getKerning(const wchar_t charcode);

            wchar_t charcode;
            unsigned int id;
            size_t width;
            size_t height;
            int offset_x;
            int offset_y;
            float advance_x;
            float advance_y;
            float s0;
            float t0;
            float s1;
            float t1;
            std::vector<GLGlyphKerning> kerning;
            int outline_type;
            float outline_thickness;
        };
    }
}
#endif	/* GLGLYPH_H */

