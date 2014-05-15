/* 
 * File:   FontManager.h
 * Author: chris
 *
 * Created on February 12, 2014, 2:51 PM
 */

#ifndef FONTMANAGER_H
#define	FONTMANAGER_H

#include "../../LOG/Source.h"

#include "Font.h"
#include "../../MEM/Pool.h"
#include "../../SYS/Reference.h"
#include <map>

namespace REND {
    namespace FONTS {
        class Font;

        class FontManager: public LOG::Source {
        public:
            typedef std::map<unsigned int, Font*> tFontMap;
            FontManager();
            virtual ~FontManager();
            SYS::Handle<Font> getFont(const FontDescription& description);
            SYS::Handle<Font>* getFontPointer(const FontDescription& description);
            void showInfo();
        protected:
            virtual Font* loadFont(const FontDescription& description) = 0;
            MEM::Pool<SYS::Reference<Font> > m_fontReferencePool;
        private:
            tFontMap m_fontMap;
        };
    }
}
#endif	/* FONTMANAGER_H */

