/* 
 * File:   SpriteInstance.h
 * Author: chris
 *
 * Created on June 18, 2014, 12:29 PM
 */

#ifndef SPRITEINSTANCE_H
#define	SPRITEINSTANCE_H

#include "../SYS/Handle.h"
#include "Sprite.h"
#include "../MATH/vec234.h"

namespace REND {

    class SpriteInstance: public SYS::Handle<REND::Sprite> {
    public:
        SpriteInstance(const SYS::Handle<REND::Sprite>& spriteHandle);
        virtual ~SpriteInstance();
        
        void render(REND::Renderer& renderer);
        void setPosition(float x, float y);
        void setPosition(const MATH::vec2& position );
        
        bool isFlippedH() const { return ((m_flippedH == GL_TRUE) ? true : false); }
        bool isFlippedV() const { return ((m_flippedV == GL_TRUE) ? true : false); }
        
        void setFlippedH(bool flipped) { m_flippedH = (flipped ? GL_TRUE : GL_FALSE); }
        void setFlippedV(bool flipped) { m_flippedV = (flipped ? GL_TRUE : GL_FALSE); }
    private:
        MATH::vec2 m_position;
        int m_flippedH;
        int m_flippedV;
        
        REND::UniformSetting* m_flippedHSetting;
        REND::UniformSetting* m_flippedVSetting;
    };
}
#endif	/* SPRITEINSTANCE_H */

