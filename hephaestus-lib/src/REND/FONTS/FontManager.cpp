/* 
 * File:   FontManager.cpp
 * Author: chris
 * 
 * Created on February 12, 2014, 2:51 PM
 */

#include "FontManager.h"
#include "../../UTIL/hash.h"
#include "../../ERR/ERR.h"
#include "../../LOG/Core.h"

#define MAX_FONTS 100

#define NAME "FontManager"

namespace REND {
    namespace FONTS {

        FontManager::FontManager()
        : m_fontReferencePool(MAX_FONTS) {
        }

        FontManager::~FontManager() {
            // delete the fonts
            for (tFontMap::iterator i = m_fontMap.begin(), e = m_fontMap.end();
                    i != e; ++i)
                delete (*i).second;
        }

        SYS::Handle<Font> FontManager::getFont(const FontDescription& description) {
            unsigned int hash = description.getHash();
            tFontMap::iterator i = m_fontMap.find(hash);
            if (i != m_fontMap.end()) {
                // found
                return (*i).second->getHandle();
            } else {
                // not found
                L(normal) << "Font: " << description.getFontName() << " size: " << description.getFontSize() << " hash: " << hash << " not found.";
                // try to load it
                Font* font = loadFont(description);
                if (font) {
                    m_fontMap.insert(std::pair<unsigned int, Font*>(hash, font));
                    return font->getHandle();
                }

                // if all fails
                THROWS("Unable to load font " + description.getFontName());
            }
        }

        SYS::Handle<Font>* FontManager::getFontPointer(const FontDescription& description) {
            unsigned int hash = description.getHash();
            tFontMap::iterator i = m_fontMap.find(hash);
            if (i != m_fontMap.end()) {
                // found
                return (*i).second->getHandlePtr();
            } else {
                // not found
                L(normal) << "Font: " << description.getFontName() << " size: " << description.getFontSize() << " hash: " << hash << " not found. Loading...";
                // try to load it
                Font* font = loadFont(description);
                if (font) {
                    m_fontMap.insert(std::pair<unsigned int, Font*>(hash, font));
                    return font->getHandlePtr();
                }

                // if all fails
                THROWS("Unable to load font " + description.getFontName());
            }
        }

        void FontManager::showInfo() {
            for (tFontMap::iterator i = m_fontMap.begin(), e = m_fontMap.end();
                    i != e; ++i)
                L(normal) << (*i).second->getFontDescription().getFontName() << " "
                << (*i).second->getFontDescription().getFontSize() << " "
                << (*i).second->getReferenceCount();
        }


    }
}
