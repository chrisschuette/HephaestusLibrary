/* 
 * File:   TextureGlyph.h
 * Author: chris
 *
 * Created on February 6, 2014, 10:39 PM
 */

#ifndef TEXTUREGLYPH_H
#define	TEXTUREGLYPH_H

#include "../../MEM/Vector.h"

namespace GL {
    namespace FONTS {

        class TextureGlyph {
        public:
            TextureGlyph();
            virtual ~TextureGlyph();
            float getKerning(const wchar_t charcode);
        public:
            /**
             * Wide character this glyph represents
             */
            wchar_t charcode;

            /**
             * Glyph id (used for display lists)
             */
            unsigned int id;

            /**
             * Glyph's width in pixels.
             */
            size_t width;

            /**
             * Glyph's height in pixels.
             */
            size_t height;

            /**
             * Glyph's left bearing expressed in integer pixels.
             */
            int offset_x;

            /**
             * Glyphs's top bearing expressed in integer pixels.
             *
             * Remember that this is the distance from the baseline to the top-most
             * glyph scanline, upwards y coordinates being positive.
             */
            int offset_y;

            /**
             * For horizontal text layouts, this is the horizontal distance (in
             * fractional pixels) used to increment the pen position when the glyph is
             * drawn as part of a string of text.
             */
            float advance_x;

            /**
             * For vertical text layouts, this is the vertical distance (in fractional
             * pixels) used to increment the pen position when the glyph is drawn as
             * part of a string of text.
             */
            float advance_y;

            /**
             * First normalized texture coordinate (x) of top-left corner
             */
            float s0;

            /**
             * Second normalized texture coordinate (y) of top-left corner
             */
            float t0;

            /**
             * First normalized texture coordinate (x) of bottom-right corner
             */
            float s1;

            /**
             * Second normalized texture coordinate (y) of bottom-right corner
             */
            float t1;

            /**
             * A vector of kerning pairs relative to this glyph.
             */
            MEM::Vector * kerning;

            /**
             * Glyph outline type (0 = None, 1 = line, 2 = inner, 3 = outer)
             */
            int outline_type;

            /**
             * Glyph outline thickness
             */
            float outline_thickness;

        };
    }
}
#endif	/* TEXTUREGLYPH_H */

