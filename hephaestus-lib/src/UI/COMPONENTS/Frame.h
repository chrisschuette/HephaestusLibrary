/* 
 * File:   Frame.h
 * Author: chris
 *
 * Created on May 23, 2014, 9:33 PM
 */

#ifndef FRAME_H
#define	FRAME_H

#include "../View.h"

namespace UI {
    namespace COMPONENTS {

        class Frame : public View {
        public:
            Frame();
            virtual ~Frame();

            bool hasBackground() const { return m_background; }
            void setBackground(bool background);
            void setBackgroundColor(float r, float g, float b, float a);
            const MATH::vec4& getBackgroundColor() const {
                return m_backgroundColor;
            }
        private:
            MATH::vec4 m_backgroundColor;
            bool m_background;
        };
    }
}
#endif	/* FRAME_H */

