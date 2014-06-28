/* 
 * File:   GLTexture.cpp
 * Author: chris
 * 
 * Created on March 23, 2014, 3:26 PM
 */

#include "GLTexture.h"
#include "../LOG/Core.h"

#define NAME "GLTexture"

namespace GL {

    GLTexture::GLTexture()
    : REND::Texture()
    , m_uploaded(false) {
        ilGenImages(1, &m_imageName); // Grab a new image name.
    }

    GLTexture::GLTexture(GLuint textureName)
    : REND::Texture()
    , m_uploaded(true)
    , m_textureName(textureName) {
    }

    GLTexture::GLTexture(const MATH::ivec2& dimensions)
    : REND::Texture()
    , m_uploaded(true) {
        setTextureDimensions(dimensions.x, dimensions.y);
        glGenTextures(1, &m_textureName);
        glBindTexture(GL_TEXTURE_2D, m_textureName);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, dimensions.x, dimensions.y, 0, GL_RGBA, GL_FLOAT, NULL);

    }

    GLTexture::GLTexture(int width, int height)
    : REND::Texture()
    , m_uploaded(true) {
        setTextureDimensions(width, height);
        glGenTextures(1, &m_textureName);
        glBindTexture(GL_TEXTURE_2D, m_textureName);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
    }

    GLTexture::~GLTexture() {
        ilDeleteImages(1, &m_imageName);
    }

    void GLTexture::loadImageData(unsigned char * data, int bytes) {
        ilBindImage(m_imageName);
        ilLoadL(IL_TYPE_UNKNOWN, data, bytes);

        m_textureInfo.width = ilGetInteger(IL_IMAGE_WIDTH);
        m_textureInfo.height = ilGetInteger(IL_IMAGE_HEIGHT);
        m_textureInfo.depth = ilGetInteger(IL_IMAGE_BPP);

        // debug
        L(normal) << "w: " << m_textureInfo.width << " h: "
                << m_textureInfo.height << " bpp: " << m_textureInfo.depth;
    }

    bool GLTexture::upload() {
        if (m_uploaded) {
            L(error) << "Texture already uploaded";
            return false;
        }

        // Generate a new texture
        glGenTextures(1, &m_textureName);
        //L(normal) << "texture name: " << m_textureName;

        // Bind the texture to a name
        glBindTexture(GL_TEXTURE_2D, m_textureName);
        ilBindImage(m_imageName);

        // Set texture clamping method
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        // Set texture interpolation method to use linear interpolation (no MIPMAPS)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Specify the texture specification
        glTexImage2D(GL_TEXTURE_2D, // Type of texture
                0, // Pyramid level (for mip-mapping) - 0 is the top level
                ilGetInteger(IL_IMAGE_FORMAT), // Internal pixel format to use. Can be a generic type like GL_RGB or GL_RGBA, or a sized type
                m_textureInfo.width, // Image width
                m_textureInfo.height, // Image height
                0, // Border width in pixels (can either be 1 or 0)
                ilGetInteger(IL_IMAGE_FORMAT), // ilGetInteger(IL_IMAGE_FORMAT), // Format of image pixel data
                GL_UNSIGNED_BYTE, // Image data type
                ilGetData()); // The actual image data itself

        m_uploaded = true;
        return true;
    }
}
