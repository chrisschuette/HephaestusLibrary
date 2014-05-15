/* 
 * File:   Font.cpp
 * Author: chris
 * 
 * Created on February 12, 2014, 2:50 PM
 */

#include "Font.h"

namespace REND {
    namespace FONTS {
Font::Font(MEM::Pool<SYS::Reference<Font> >& referencePool, const FontDescription& fontDescription)
: SYS::IsReferenceCounted<Font>(referencePool)
, m_fontDescription(fontDescription)
{
}

Font::~Font() {
}
    }
}