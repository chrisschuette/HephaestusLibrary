/* 
 * File:   FontDescription.h
 * Author: chris
 *
 * Created on February 12, 2014, 2:52 PM
 */

#ifndef FONTDESCRIPTION_H
#define	FONTDESCRIPTION_H

#include <string>

namespace REND {
    namespace FONTS {
class FontDescription {
public:
    FontDescription(std::string fontName, unsigned int size);
    virtual ~FontDescription();
    const std::string& getFontName() const { return m_fontName; }
    unsigned int getFontSize() const { return m_size; }
    unsigned int getHash() const;
private:
    std::string m_fontName;
    unsigned int m_size;
};
    }
}
#endif	/* FONTDESCRIPTION_H */

