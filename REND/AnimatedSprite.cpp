/* 
 * File:   AnimatedSprite.cpp
 * Author: chris
 * 
 * Created on March 23, 2014, 11:30 PM
 */

#include "AnimatedSprite.h"
#include "../ERR/ERR.h"
#include "../UTIL/string.h"

namespace REND {

    const AnimatedSprite::FrameInfo& AnimatedSprite::SequenceInfo::getFrameInfo(unsigned int i) const {
        if (frameInfos.size() == 0)
            THROWS("Empty sequence");

        if (i >= frameInfos.size())
            if (loop)
                i = i % frameInfos.size();
            else
                THROWS("Invalid image " + UTIL::toString(i) + " in sequence");

        return frameInfos.at(i);
    }

    AnimatedSprite::AnimatedSprite(const SYS::Handle<REND::Texture>& texture, const REND::ShaderProgram* shaderProgram)
    : Sprite(texture, shaderProgram)
    , m_currentSequence(-1)
    , m_currentFrame(-1)
    , m_startTimeOfCurrentFrame(-1)
    , m_sequenceFinished(true) {
    }

    AnimatedSprite::~AnimatedSprite() {
    }
    
    void AnimatedSprite::startSequence(unsigned int s) {
         if (s >= m_frameInfos.size())
            THROWS("Invalid sequence: " + UTIL::toString(s));
         if (m_frameInfos.at(s).frameInfos.size() == 0)
            THROWS("Empty sequence: " + UTIL::toString(s));
         
         m_currentSequence = s;
         m_currentFrame = -1;
         m_sequenceFinished = false;
    }

    void AnimatedSprite::addSequence(const std::vector<FrameInfo>& sequence, bool loop) {
        m_frameInfos.push_back(SequenceInfo(sequence, loop));
    }

    void AnimatedSprite::update(unsigned long int t) {

        if (m_sequenceFinished || (m_currentSequence < 0))
            return;

        // start of new sequence
        if(m_currentFrame == -1) {
            m_currentFrame = 0;
            m_startTimeOfCurrentFrame = t;
        }
        
        const AnimatedSprite::SequenceInfo& sequenceInfo = getSequence(m_currentSequence);
        const AnimatedSprite::FrameInfo& frameInfo = sequenceInfo.getFrameInfo(m_currentFrame);
        unsigned long int elapsed = t - m_startTimeOfCurrentFrame;

        if (elapsed > frameInfo.dt) {
            if(sequenceInfo.loop) {
                m_currentFrame = (m_currentFrame+1) % sequenceInfo.frameInfos.size();
                m_startTimeOfCurrentFrame = t;
            } else {
                if( m_currentFrame >= (sequenceInfo.frameInfos.size()-1) ) {
                    m_sequenceFinished = true;
                } else {
                    m_currentFrame++;
                    m_startTimeOfCurrentFrame = t;
                }
            }
        }
    }

    const AnimatedSprite::SequenceInfo& AnimatedSprite::getSequence(unsigned int s) const {
        if (s >= m_frameInfos.size())
            THROWS("Invalid sequence: " + UTIL::toString(s));
        return m_frameInfos.at(s);
    }

    const AnimatedSprite::FrameInfo& AnimatedSprite::getFrameInfo(unsigned int s, unsigned int i) const {
        if (s >= m_frameInfos.size())
            THROWS("Invalid sequence: " + UTIL::toString(s));

        const SequenceInfo& seq = m_frameInfos.at(s);

        if (seq.frameInfos.size() == 0)
            THROWS("Empty sequence: " + UTIL::toString(s));

        if (i >= seq.frameInfos.size())
            if (seq.loop)
                i = i % seq.frameInfos.size();
            else
                THROWS("Invalid image " + UTIL::toString(i) + " in sequence " + UTIL::toString(s));

        return seq.frameInfos.at(i);
    }


}
