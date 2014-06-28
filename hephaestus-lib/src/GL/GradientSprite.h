/* 
 * File:   GradientSprite.h
 * Author: chris
 *
 * Created on June 18, 2014, 5:28 PM
 */

#ifndef GLGRADIENTSPRITE_H
#define	GLGRADIENTSPRITE_H

#include "../REND/GradientSprite.h"

namespace GL {

    class GradientSprite : public REND::GradientSprite {
    public:
        GradientSprite(const SYS::Handle<REND::Texture>& texture, REND::ShaderProgramInstance shaderProgram);
        virtual ~GradientSprite();

        virtual void draw(REND::Renderer& renderer) const;

    private:

    };
}
#endif	/* GLGRADIENTSPRITE_H */

