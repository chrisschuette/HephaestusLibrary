/* 
 * File:   Sprite.h
 * Author: chris
 *
 * Created on March 23, 2014, 5:27 PM
 */

#ifndef SPRITE_H
#define	SPRITE_H

#include "Renderable.h"
#include "ShaderProgramInstance.h"
#include "../SYS/Handle.h"
#include "Texture.h"
#include "../MATH/vec234.h"
#include "UniformSetting.h"

namespace REND {

    class Sprite : public REND::Renderable {
    public:
        Sprite(RenderBuffer* renderBuffer, const SYS::Handle<REND::Texture>& texture, ShaderProgramInstance shaderProgram);
        virtual ~Sprite();
        
        virtual int getWidth() const;
        virtual int getHeight() const;
    protected:
        SYS::Handle<REND::Texture> m_texture;
        UniformSetting* m_sprite;

    };
}
#endif	/* SPRITE_H */

