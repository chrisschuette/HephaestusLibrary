/* 
 * File:   AnimatedSprite.h
 * Author: chris
 *
 * Created on March 23, 2014, 11:30 PM
 */

#ifndef ANIMATEDSPRITE_H
#define	ANIMATEDSPRITE_H

#include "Sprite.h"
#include <vector>

namespace REND {
    class AnimatedSprite: public Sprite {
    public:
        struct FrameInfo {
            int x, y, w, h, dt;
        };
        struct SequenceInfo {
            SequenceInfo(const std::vector<FrameInfo>& i, bool l) : frameInfos(i), loop(l) {}
            const FrameInfo& getFrameInfo(unsigned int i) const;

            bool loop;
            std::vector<FrameInfo> frameInfos;
        };
    public:
        AnimatedSprite(const SYS::Handle<REND::Texture>& texture, const REND::ShaderProgram* shaderProgram);
        virtual ~AnimatedSprite();
        
        void addSequence(const std::vector<FrameInfo>& sequence, bool loop = true);
        const SequenceInfo& getSequence(unsigned int s) const;
        
        void startSequence(unsigned int s);
        
        void update(unsigned long int t);
    protected:
        const FrameInfo& getFrameInfo(unsigned int s, unsigned int i) const;
    protected:
        int m_currentSequence;
        int m_currentFrame;
        std::vector< SequenceInfo > m_frameInfos;
        long unsigned int m_startTimeOfCurrentFrame;
        bool m_sequenceFinished;
        
    };
}
#endif	/* ANIMATEDSPRITE_H */

