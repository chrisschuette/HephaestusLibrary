/* 
 * File:   AnimatedSprite.cpp
 * Author: chris
 * 
 * Created on June 19, 2014, 4:47 PM
 */

#include "AnimatedSprite.h"
#include "../ERR/ERR.h"
#include "../LOG/Core.h"
#include <assert.h>

#define NAME "AnimatedSprite"

namespace REND {

    AnimatedSprite::AnimatedSprite(RenderBuffer* renderBuffer, const SYS::Handle<REND::Texture>& texture, ShaderProgramInstance shaderProgram, const MATH::ivec2& spriteDimensions)
    : Sprite(renderBuffer, texture, shaderProgram)
    , m_currentFrame(0)
    , m_currentAnimation(0)
    , m_loop(true)
    , m_frameDisplayTime(0)
    , m_spriteDimensions(spriteDimensions) {
        m_TSetting = shaderProgram.createUniformSetting("T", true);
        m_flippedHSetting = shaderProgram.createUniformSetting("flippedH", true);
        m_flippedVSetting = shaderProgram.createUniformSetting("flippedV", true);
        m_atlasDimensions.x = texture->getTextureWidth();
        m_atlasDimensions.y = texture->getTextureHeight();
    }

    AnimatedSprite::~AnimatedSprite() {
    }

    int AnimatedSprite::getWidth() const {
        return m_spriteDimensions.x;
    }
    
    int AnimatedSprite::getHeight() const {
        return m_spriteDimensions.y;
    }

    void AnimatedSprite::addFrame(const Frame& frame) {
        std::pair < std::map<std::string, unsigned int>::iterator, bool> i = m_frameIndex.insert(std::pair<std::string, unsigned int>(frame.name, m_frames.size()));
        if (!i.second)
            THROWS("Frame insert failed.");
        m_frames.push_back(frame);
    }

    int AnimatedSprite::getFrameIndex(const std::string& name) {
        std::map<std::string, unsigned int>::const_iterator i = m_frameIndex.find(name);
        if (i != m_frameIndex.end())
            return (*i).second;
        return -1;
    }

    void AnimatedSprite::startAnimation(const std::string& name, bool loop) {
        std::map<std::string, unsigned int>::const_iterator i = m_animationIndex.find(name);
        if (i == m_animationIndex.end())
            THROWS("Unknown animation: " + name);
        m_currentAnimation = (*i).second;
        m_currentFrame = 0;
        m_loop = loop;
    }

    void AnimatedSprite::addAnimation(const std::string name, const std::vector<std::string>& frameNames, int tpf, bool flippedH, bool flippedV) {
        std::vector<unsigned int> frameIndices;
        for (std::vector<std::string>::const_iterator i = frameNames.begin(), e = frameNames.end(); i != e; ++i) {
            int index = getFrameIndex((*i));
            L(normal) << (*i) << " : " << index;
            if (index < 0)
                THROWS("Invalid frame " + (*i));
            frameIndices.push_back((unsigned int) index);
        }

        Animation animation;
        animation.name = name;
        animation.frames = frameIndices;
        animation.flippedH = flippedH;
        animation.flippedV = flippedV;
        animation.tpf = tpf;

        std::pair < std::map<std::string, unsigned int>::iterator, bool> i = m_animationIndex.insert(std::pair<std::string, unsigned int>(animation.name, m_animations.size()));
        if (!i.second)
            THROWS("Animation insert failed");
        m_animations.push_back(animation);
    }

    void AnimatedSprite::update(unsigned long int time, unsigned long int diff) {
        m_frameDisplayTime += diff;
        if (m_frameDisplayTime > m_animations[m_currentAnimation].tpf) {
            m_frameDisplayTime = 0;
            if (m_loop) {
                m_currentFrame++;
                m_currentFrame = m_currentFrame % m_animations[m_currentAnimation].frames.size();
            } else {
                if (m_currentFrame < (m_animations[m_currentAnimation].frames.size() - 1))
                    m_currentFrame++;
            }
        }
    }
}
