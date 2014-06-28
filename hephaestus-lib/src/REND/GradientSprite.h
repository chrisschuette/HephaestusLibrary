/* 
 * File:   GradientSprite.h
 * Author: chris
 *
 * Created on June 18, 2014, 5:19 PM
 */

#ifndef RENDGRADIENTSPRITE_H
#define	RENDGRADIENTSPRITE_H

#include "Sprite.h"

namespace REND {
    namespace GradientSprite_CONST {
        const int MAX_STOPS = 4;
    }
    class GradientSprite : public REND::Sprite {
    public:
        struct GradientStop {
            std::string position_name;
            float position;
            std::string color_name;
            MATH::vec4 rgba;
        };
    public:
        GradientSprite(RenderBuffer* renderBuffer, const SYS::Handle<REND::Texture>& texture, ShaderProgramInstance shaderProgram);
        virtual ~GradientSprite();
        void addStop(float position, float r, float g, float b, float a);
        void addStop(float position, const MATH::vec4& color);
    protected:
        int m_N;
        GradientStop m_stops[GradientSprite_CONST::MAX_STOPS];
    };
}
#endif	/* RENDGRADIENTSPRITE_H */

