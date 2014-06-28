/* 
 * File:   GradientSprite.cpp
 * Author: chris
 * 
 * Created on June 18, 2014, 5:19 PM
 */

#include "GradientSprite.h"
#include "../UTIL/string.h"

#include <assert.h>

namespace REND {

    GradientSprite::GradientSprite(RenderBuffer* renderBuffer, const SYS::Handle<REND::Texture>& texture, ShaderProgramInstance shaderProgram)
    : REND::Sprite(renderBuffer, texture, shaderProgram)
    , m_N(0) {
    }

    GradientSprite::~GradientSprite() {
    }

    void GradientSprite::addStop(float position, const MATH::vec4& color) {
        assert(m_N < GradientSprite_CONST::MAX_STOPS);
        m_stops[m_N].color_name = "positions[" + UTIL::toString(m_N) + "].color";
        m_stops[m_N].rgba = color;
        m_stops[m_N].position_name = "positions[" + UTIL::toString(m_N) + "].position";
        m_stops[m_N].position = position;
        m_N++;
    }

    void GradientSprite::addStop(float position, float r, float g, float b, float a) {
        assert(m_N < GradientSprite_CONST::MAX_STOPS);
        m_stops[m_N].color_name = "positions[" + UTIL::toString(m_N) + "].color";
        m_stops[m_N].rgba.r = r;
        m_stops[m_N].rgba.g = g;
        m_stops[m_N].rgba.b = b;
        m_stops[m_N].rgba.a = a;
        m_stops[m_N].position_name = "positions[" + UTIL::toString(m_N) + "].position";
        m_stops[m_N].position = position;
        m_N++;
    }


}