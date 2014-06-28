/* 
 * File:   SpriteInstance.cpp
 * Author: chris
 * 
 * Created on June 18, 2014, 12:29 PM
 */

#include "SpriteInstance.h"

namespace REND {

    SpriteInstance::SpriteInstance(const SYS::Handle<REND::Sprite>& spriteHandle)
    : SYS::Handle<REND::Sprite>(spriteHandle)
    , m_flippedH(GL_FALSE)
    , m_flippedV(GL_FALSE)
    , m_flippedHSetting(0)
    , m_flippedVSetting(0) {
        if (get()) {
            const REND::Sprite* sprite = get();
            m_flippedHSetting = sprite->getShaderInstance().createUniformSetting("flippedH", false);
            m_flippedVSetting = sprite->getShaderInstance().createUniformSetting("flippedV", false);
        }
        m_position.x = 0;
        m_position.y = 0;
    }

    SpriteInstance::~SpriteInstance() {
        if (m_flippedHSetting)
            delete m_flippedHSetting;
        if (m_flippedVSetting)
            delete m_flippedVSetting;
    }

    void SpriteInstance::render(REND::Renderer& renderer) {
        if (get() && get()->getShaderInstance().get()) {
            renderer.PushMatrix();
            renderer.Translate(m_position.x, m_position.y, 0);
            get()->activateProgram(renderer);

            // flipped?
            m_flippedHSetting->set(&m_flippedH);
            m_flippedVSetting->set(&m_flippedV);

            get()->draw(renderer);
            renderer.PopMatrix();
        }
    }

    void SpriteInstance::setPosition(float x, float y) {
        m_position.x = x;
        m_position.y = y;
    }

    void SpriteInstance::setPosition(const MATH::vec2& position) {
        m_position = position;
    }

}