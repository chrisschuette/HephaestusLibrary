/* 
 * File:   FontDescription.cpp
 * Author: chris
 * 
 * Created on February 12, 2014, 2:52 PM
 */

#include "FontDescription.h"
#include <boost/functional/hash.hpp>

namespace REND {
    namespace FONTS {

        FontDescription::FontDescription(std::string fontName, unsigned int size)
        : m_fontName(fontName)
        , m_size(size) {
        }

        FontDescription::~FontDescription() {
        }

        unsigned int FontDescription::getHash() const {
            boost::hash<std::string> string_hash;
            return string_hash(m_fontName) + m_size;
        }

    }
}
