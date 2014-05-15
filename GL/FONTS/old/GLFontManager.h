/* 
 * File:   GLFontManager.h
 * Author: chris
 *
 * Created on February 12, 2014, 3:14 PM
 */

#ifndef GLFONTMANAGER_H
#define	GLFONTMANAGER_H

#include "../../REND/FONTS/FontManager.h"
#include "../GLTextureAtlas.h"
#include "../../LOG/Source.h"

namespace GL {
    namespace FONTS {

        class GLFontManager : public REND::FONTS::FontManager, public LOG::Source {
        public:
            GLFontManager();
            virtual REND::FONTS::Font* loadFont(const REND::FONTS::FontDescription& fontDescription);
            virtual ~GLFontManager();
        private:
            GLTextureAtlas m_textureAtlas;
        };
    }
}
#endif	/* GLFONTMANAGER_H */

