/* 
 * File:   Button.h
 * Author: chris
 *
 * Created on May 23, 2014, 8:35 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "../Component.h"
#include <boost/signals2.hpp>

#include "../../MATH/vec234.h"

namespace UI {
    namespace COMPONENTS {

        class Button : public Component {
        public:

            enum TEXT_ALIGN {
                LEFT, RIGHT, CENTER
            };

            enum VTEXT_ALIGN {
                TOP, BOTTOM, MIDDLE
            };
            typedef boost::signals2::signal<void () > click_signal_type;
            typedef click_signal_type::slot_type click_slot_type;
        public:
            Button();
            Button(std::string caption);
            virtual ~Button();
            bool click(const click_slot_type& s);
            click_signal_type onClick;


            void setTextColor(float r, float g, float b, float a);
            
            void setBackgroundColor(float r, float g, float b, float a);
            void setBackgroundColor(const MATH::vec4& color);
            const MATH::vec4& getBackgroundColor() const;

            const std::string& getText() const {
                return m_text;
            }
            void setText(const std::string& text);

            const MATH::vec4& getTextColor() const {
                return m_textColor;
            }

            TEXT_ALIGN getTextAlign() const {
                return m_textAlign;
            }

            void setTextAlign(TEXT_ALIGN align) {
                m_textAlign = align;
            }

            VTEXT_ALIGN getVTextAlign() const {
                return m_VTextAlign;
            }

            void setVTextAlign(VTEXT_ALIGN valign) {
                m_VTextAlign = valign;
            }

        private:
            MATH::vec4 m_backgroundColor;

            std::string m_text;
            MATH::vec4 m_textColor;
            TEXT_ALIGN m_textAlign;
            VTEXT_ALIGN m_VTextAlign;
        };
    }
}
#endif	/* BUTTON_H */

