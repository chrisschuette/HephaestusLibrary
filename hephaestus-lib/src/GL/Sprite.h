/* 
 * File:   Sprite.h
 * Author: chris
 *
 * Created on June 14, 2014, 12:23 PM
 */

#ifndef GLSPRITE_H
#define	GLSPRITE_H

#include "../REND/Sprite.h"

namespace GL {

    class Sprite: public REND::Sprite {
    public:
        Sprite(const SYS::Handle<REND::Texture>& texture, REND::ShaderProgramInstance shaderProgram);
        virtual ~Sprite();

        virtual void draw(REND::Renderer& renderer) const;

    private:

    };
}
#endif	/* GLSPRITE_H */

