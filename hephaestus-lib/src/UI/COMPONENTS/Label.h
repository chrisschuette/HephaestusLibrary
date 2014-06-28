/* 
 * File:   Label.h
 * Author: chris
 *
 * Created on June 11, 2014, 10:57 PM
 */

#ifndef LABEL_H
#define	LABEL_H

#include "../Component.h"
#include "../../MATH/vec234.h"

namespace UI {
    namespace COMPONENTS {
        
        class Label : public Component {
        public:
            enum TEXT_ALIGN { LEFT, RIGHT, CENTER };
            enum VTEXT_ALIGN { TOP, BOTTOM, MIDDLE };
        public:
            Label();
            Label(std::string text);
            virtual ~Label();
            
            void setBackgroundColor(float r, float g, float b, float a);
            const MATH::vec4& getBackgroundColor() const;
            
            const std::string& getText() const { return m_text; }
            void setText(const std::string& text);
            
            const MATH::vec4& getTextColor() const { return m_textColor; }
            
            TEXT_ALIGN getTextAlign() const { return m_textAlign; }
            void setTextAlign(TEXT_ALIGN align) { m_textAlign = align; }
            VTEXT_ALIGN getVTextAlign() const { return m_VTextAlign; }
            void setVTextAlign(VTEXT_ALIGN valign) { m_VTextAlign = valign; }
            
            void setBackground(bool background) { m_background = background; }
            bool hasBackground() const { return m_background; }
        private:
            bool m_background;
            MATH::vec4 m_backgroundColor;
            
            std::string m_text;
            MATH::vec4 m_textColor;
            TEXT_ALIGN m_textAlign;
            VTEXT_ALIGN m_VTextAlign;
        };
    }
}
#endif	/* LABEL_H */

