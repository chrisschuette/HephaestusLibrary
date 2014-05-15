/* 
 * File:   GLFontManager.cpp
 * Author: chris
 * 
 * Created on February 12, 2014, 3:14 PM
 */

#include "GLFontManager.h"
#include "TextureFont.h"

namespace GL {
    namespace FONTS {

        GLFontManager::GLFontManager()
        : REND::FONTS::FontManager()
        , LOG::Source("GLFontManager")
        , m_textureAtlas(600,600,1)        
        {
        }

        GLFontManager::~GLFontManager() {
        }

        const REND::FONTS::Font* GLFontManager::loadFont(const REND::FONTS::FontDescription& fontDescription) {
            L(normal) << "Load Font " << fontDescription.getFontName() << " " << fontDescription.getFontSize();
            
            // do some filename resolution here
            std::string filename = "fonts/Vera.ttf"; 
            
            const wchar_t *cache = L" !\"#$%&'()*+,-./0123456789:;<=>?"
            L"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
            L"`abcdefghijklmnopqrstuvwxyz{|}~";
            
            TextureFont* textureFont = new TextureFont(fontDescription.getFontName(), fontDescription.getFontSize(),
                    filename, &m_textureAtlas);
            
            int missed = 0;
            missed += textureFont->load_glyphs(cache);
            L(normal) << "missed: " << missed;
            if(textureFont)
                addFont(fontDescription, textureFont);
            return textureFont;
        }
    }
}
