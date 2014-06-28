/* 
 * File:   AnimatedSprite.h
 * Author: chris
 *
 * Created on June 19, 2014, 4:47 PM
 */

#ifndef ANIMATEDSPRITE_H
#define	ANIMATEDSPRITE_H

#include "Sprite.h"
#include "../MATH/vec234.h"

#include <string>
#include <vector>
#include <map>

namespace REND {

    class AnimatedSprite : public Sprite {
    public:

        struct Frame {
            std::string name;
            int x;
            int y;
        };

        struct Animation {
            std::string name;
            std::vector<unsigned int> frames;
            bool flippedH;
            bool flippedV;
            int tpf;
        };
    public:
        AnimatedSprite(RenderBuffer* renderBuffer, const SYS::Handle<REND::Texture>& texture, ShaderProgramInstance shaderProgram, const MATH::ivec2& spriteDimensions);
        virtual ~AnimatedSprite();

        virtual int getWidth() const;
        virtual int getHeight() const;

        void addFrame(const Frame& frame);
        void addAnimation(const std::string name, const std::vector<std::string>& frameNames, int tpf, bool flippedH, bool flippedV);
        int getFrameIndex(const std::string& name);

        void startAnimation(const std::string& name, bool loop = true);

        void update(unsigned long int time, unsigned long int diff);
    protected:
        std::vector<Frame> m_frames;
        std::vector<Animation> m_animations;
        std::map<std::string, unsigned int> m_animationIndex;
        std::map<std::string, unsigned int> m_frameIndex;

        MATH::ivec2 m_atlasDimensions;
        MATH::ivec2 m_spriteDimensions;

        unsigned long int m_frameDisplayTime;
        unsigned int m_currentFrame;
        unsigned int m_currentAnimation;
        bool m_loop;

        UniformSetting* m_TSetting; // x, y, tw, th
        UniformSetting* m_flippedHSetting;
        UniformSetting* m_flippedVSetting;
    };
}
#endif	/* ANIMATEDSPRITE_H */

