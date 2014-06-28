/* 
 * File:   ProgressCircle.h
 * Author: chris
 *
 * Created on June 10, 2014, 10:54 PM
 */

#ifndef PROGRESSCIRCLE_H
#define	PROGRESSCIRCLE_H

#include "../View.h"

namespace UI {
    namespace COMPONENTS {

        class ProgressCircle : public View {
        public:
            ProgressCircle();
            virtual ~ProgressCircle();

            const MATH::vec4& getBackgroundColor() const {
                return m_backgroundColor;
            }

            const MATH::vec4& getCircleColor() const {
                return m_circleColor;
            }
            
            bool hasBackground() const { return m_background; }

            void setBackgroundColor(const MATH::vec4& color) {
                m_backgroundColor = color;
            }
            void setBackgroundColor(float r, float g, float b, float a);

            void setCircleColor(const MATH::vec4& color) {
                m_circleColor = color;
            }
            void setCircleColor(float r, float g, float b, float a);

            // value

            int getMaximumValue() const {
                return m_maxValue;
            }

            int getValue() const {
                return m_value;
            }

            void setMaximumValue(int maxValue);
            void setValue(int value);
            
            int getCircleThickness() const {
                return m_thickness;
            }
            
            void setCircleThickness(int thickness) {
                m_thickness = thickness;
            }

        private:
            bool m_background;
            MATH::vec4 m_backgroundColor;
            MATH::vec4 m_circleColor;
            int m_maxValue;
            int m_value;

            int m_thickness;
        };
    }
}
#endif	/* PROGRESSCIRCLE_H */

