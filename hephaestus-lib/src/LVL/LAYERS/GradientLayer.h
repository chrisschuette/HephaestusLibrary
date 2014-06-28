/* 
 * File:   GradientLayer.h
 * Author: chris
 *
 * Created on May 27, 2014, 12:46 PM
 */

#ifndef GRADIENTLAYER_H
#define	GRADIENTLAYER_H

#include "../Layer.h"
#include "../../MATH/vec234.h"
#include "../../UTIL/string.h"
#include "../../REND/ShaderProgramInstance.h"

#include <list>
#include <string>

namespace LVL {
    namespace LAYERS {
            enum GRADIENT_TYPE { LINEAR, RADIAL };

        template<int N>
        class GradientLayer : public LVL::Layer {
        public:

            struct GradientStop {
                std::string position_name;
                float position;
                std::string color_name;
                MATH::vec4 rgba;
            };
        public:

            GradientLayer(Context& context)
            : LVL::Layer(context)
            , m_shaderProgram(0) {
            }
            
            virtual ~GradientLayer() {
                if(m_shaderProgram)
                    delete m_shaderProgram;
            }

            virtual void setGradientType(GRADIENT_TYPE type) = 0;
            
            void setStop(int i, float position, float r, float g, float b, float a) {
                m_gradientStops[i].color_name = "positions[" + UTIL::toString(i) + "].color";
                m_gradientStops[i].rgba.r = r;
                m_gradientStops[i].rgba.g = g;
                m_gradientStops[i].rgba.b = b;
                m_gradientStops[i].rgba.a = a;
                m_gradientStops[i].position_name = "positions[" + UTIL::toString(i) + "].y";
                m_gradientStops[i].position = position;
            }
        protected:
            GradientStop m_gradientStops[N];
            REND::ShaderProgramInstance* m_shaderProgram;
        };
    }
}
#endif	/* GRADIENTLAYER_H */

