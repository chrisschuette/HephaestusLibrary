/* 
 * File:   AnimatedSprite.h
 * Author: chris
 *
 * Created on June 20, 2014, 4:44 PM
 */

#ifndef GLANIMATEDSPRITE_H
#define	GLANIMATEDSPRITE_H

#include "../REND/AnimatedSprite.h"

namespace GL {
    class AnimatedSprite: public REND::AnimatedSprite {
    public:
        AnimatedSprite(const SYS::Handle<REND::Texture>& texture, REND::ShaderProgramInstance shaderProgram, const MATH::ivec2& spriteDimensions);
        virtual ~AnimatedSprite();
        
        virtual void draw(REND::Renderer& renderer) const;
        
    private:

    };
}
#endif	/* GLANIMATEDSPRITE_H */

