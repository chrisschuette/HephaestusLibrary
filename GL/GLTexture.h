/* 
 * File:   GLTexture.h
 * Author: chris
 *
 * Created on March 23, 2014, 3:26 PM
 */

#ifndef GLTEXTURE_H
#define	GLTEXTURE_H

#include "../REND/Texture.h"
#include <IL/il.h>
#include <GL/glew.h>

namespace GL {

    class GLTexture: public REND::Texture {
    public:
        GLTexture();
        virtual ~GLTexture();
        
        ILuint getImageName() const {
            return m_imageName;
        }
        
        GLuint getTextureName() const {
            return m_textureName;
        }
        
        void loadImageData(unsigned char * data, int bytes);
        
        virtual bool upload();
    private:
        ILuint m_imageName;
        GLuint m_textureName;
        bool m_uploaded;
    };

}
#endif	/* GLTEXTURE_H */

