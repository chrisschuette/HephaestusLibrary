/* 
 * File:   Font.h
 * Author: chris
 *
 * Created on February 12, 2014, 2:50 PM
 */

#ifndef FONT_H
#define	FONT_H

#include "../../SYS/IsReferenceCounted.h"
#include "../../MATH/vec234.h"
#include "FontDescription.h"

namespace REND {
    class RenderBuffer;
    namespace FONTS {
        class Font: public SYS::IsReferenceCounted<Font> {
        public:
            Font(MEM::Pool<SYS::Reference<Font> >& referencePool, const FontDescription& fontDescription);
            virtual ~Font();
            const FontDescription& getFontDescription() { return m_fontDescription; }
            virtual float getAscender() const = 0;
            virtual float getDescender() const = 0;
            virtual float getLineGap() const = 0;
            virtual float getLineHeight() const = 0;
            virtual RenderBuffer* createText(std::string text, MATH::vec2& pen) = 0;
        protected:
            FontDescription m_fontDescription;
        };
    }
}
#endif	/* FONT_H */

