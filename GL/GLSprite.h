/* 
 * File:   GLSprite.h
 * Author: chris
 *
 * Created on March 23, 2014, 6:29 PM
 */

#ifndef GLSPRITE_H
#define	GLSPRITE_H

#include "../REND/Sprite.h"
#include "GLVertexBuffer.h"

namespace GL {
    class GLShaderProgram;
    class GLSprite: public REND::Sprite {
    public:
        GLSprite(const SYS::Handle<REND::Texture>& texture, const REND::ShaderProgram* shaderProgram);
        virtual ~GLSprite();
        
        virtual void draw(const REND::Renderer& renderer);

    private:
        GLVertexBuffer m_vertexBuffer;
    };
}
#endif	/* GLSPRITE_H */

