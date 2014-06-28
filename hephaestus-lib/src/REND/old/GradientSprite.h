/* 
 * File:   GradientSprite.h
 * Author: chris
 *
 * Created on May 28, 2014, 12:50 AM
 */

#ifndef GRADIENTSPRITE_H
#define	GRADIENTSPRITE_H

#include "Sprite.h"
#include "../UTIL/string.h"

namespace REND {

    template <int N>
    class GradientSprite : public Sprite {
    public:

        struct GradientStop {
            std::string position_name;
            float position;
            std::string color_name;
            MATH::vec4 rgba;
        };
    public:

        GradientSprite(RenderBuffer* renderBuffer, const SYS::Handle<REND::Texture>& texture, const REND::ShaderProgram* shaderProgram)
        : Sprite(renderBuffer, texture, shaderProgram) {
        }

        void setStop(int i, float position, float r, float g, float b, float a) {
            m_gradientStops[i].color_name = "positions[" + UTIL::toString(i) + "].color";
            m_gradientStops[i].rgba.r = r;
            m_gradientStops[i].rgba.g = g;
            m_gradientStops[i].rgba.b = b;
            m_gradientStops[i].rgba.a = a;
            m_gradientStops[i].position_name = "positions[" + UTIL::toString(i) + "].y";
            m_gradientStops[i].position = position;
        }

        virtual ~GradientSprite() {}
    protected:
        std::list<GradientStop> m_gradientStops[N];

    };
}
#endif	/* GRADIENTSPRITE_H */

