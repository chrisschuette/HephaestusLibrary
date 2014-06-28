/* 
 * File:   Context.h
 * Author: chris
 *
 * Created on May 23, 2014, 8:04 PM
 */

#ifndef UICONTEXT_H
#define	UICONTEXT_H

#include "../REND/Renderer.h"
#include "../REND/ShaderManager.h"
#include "../REND/FONTS/FontManager.h"
#include "../REND/TextureManager.h"

namespace UI {
    class Renderer;
    class Context {
    public:
        virtual REND::Renderer& getRenderer() = 0;
        virtual REND::ShaderManager& getShaderManager() = 0;
        virtual REND::FONTS::FontManager& getFontManager() = 0;
        virtual REND::TextureManager& getTextureManager() = 0;
    };
}
#endif	/* UICONTEXT_H */

