/* 
 * File:   GLFontManager.h
 * Author: chris
 *
 * Created on February 13, 2014, 3:58 PM
 */

#ifndef GLFONTMANAGER_H
#define	GLFONTMANAGER_H

#include "../../REND/FONTS/FontManager.h"
#include "../GLTextureAtlas.h"
#include "../../MATH/vec234.h"


namespace GL {
    class GLVertexBuffer;
    namespace FONTS {

        namespace GLFontManager_CONST {
            const unsigned int TextureAtlasSize = 500;
        }
        
        class GLFontManager : public REND::FONTS::FontManager {
        public:
            GLFontManager();
            virtual ~GLFontManager();
            //GLVertexBuffer* createText(const std::string& Text, SYS::Handle<REND::FONTS::Font>& fontHandle, MATH::vec2* pen);
        private:
            virtual REND::FONTS::Font* loadFont(const REND::FONTS::FontDescription& description);
            GL::GLTextureAtlas m_textureAtlas;
        };
    }
}
#endif	/* GLFONTMANAGER_H */

