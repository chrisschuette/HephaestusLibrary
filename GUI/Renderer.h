/* 
 * File:   Renderer.h
 * Author: chris
 *
 * Created on February 10, 2014, 5:03 PM
 */

#ifndef GUI_RENDERER_H
#define	GUI_RENDERER_H

#include "../REND/Renderer.h"

namespace REND {
    class ShaderManager;
    namespace FONTS {
        class FontManager;
    }
}

namespace GUI {
    class Renderer: public REND::Renderer {
    public:
        Renderer(REND::ShaderManager& shaderManager, REND::FONTS::FontManager& fontManager);
        virtual ~Renderer();
        virtual void PushMatrix() = 0;
        virtual void PopMatrix() = 0;
        virtual void Translate(int x, int y) = 0;
        REND::ShaderManager& getShaderManager() { return m_shaderManager; }
        REND::FONTS::FontManager& getFontManager() { return m_fontManager; }
    private:
        REND::ShaderManager& m_shaderManager;
        REND::FONTS::FontManager& m_fontManager;
    };
}
#endif	/* GUI_RENDERER_H */

