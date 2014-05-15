/* 
 * File:   TextureGlyphKerning.h
 * Author: chris
 *
 * Created on February 6, 2014, 11:00 PM
 */

#ifndef TEXTUREGLYPHKERNING_H
#define	TEXTUREGLYPHKERNING_H

namespace GL {
    namespace FONTS {

        class TextureGlyphKerning {
        public:
            TextureGlyphKerning();
            virtual ~TextureGlyphKerning();
        public:
            /**
             * Left character code in the kern pair.
             */
            wchar_t charcode;

            /**
             * Kerning value (in fractional pixels).
             */
            float kerning;
        };
    }
}
#endif	/* TEXTUREGLYPHKERNING_H */

