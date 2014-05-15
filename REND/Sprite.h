/* 
 * File:   Sprite.h
 * Author: chris
 *
 * Created on March 23, 2014, 5:27 PM
 */

#ifndef SPRITE_H
#define	SPRITE_H

#include "Renderable.h"
#include "../SYS/Handle.h"
#include "Texture.h"

namespace REND {
    class ShaderProgram;
    class Sprite: public REND::Renderable {
    public:
        Sprite(const SYS::Handle<REND::Texture>& texture, const REND::ShaderProgram* shaderProgram);
        virtual ~Sprite();
    protected:
        SYS::Handle<REND::Texture> m_texture;
        const ShaderProgram* m_shaderProgram;
    };
}
#endif	/* SPRITE_H */

