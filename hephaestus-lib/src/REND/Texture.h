/* 
 * File:   Texture.h
 * Author: chris
 *
 * Created on June 9, 2013, 7:59 PM
 */

#ifndef TEXTURE_H
#define	TEXTURE_H

#include <GL/glew.h>

namespace REND {
class Texture {
public:
    struct TextureInfo{
        TextureInfo() : width(-1), height(-1)
        , depth(-1) {}
        int width;
        int height;
        int depth;
    };
public:
    Texture();
    virtual ~Texture();
    
    const TextureInfo& getTextureInfo() const { return m_textureInfo; }
    int getTextureWidth() const { return m_textureInfo.width; }
    int getTextureHeight() const { return m_textureInfo.height; }
    int getTextureDepth() const { return m_textureInfo.depth; }
    
    void setTextureDimensions(int W, int H) { m_textureInfo.width = W; m_textureInfo.height = H; }
    
    virtual bool upload() = 0; 
protected:
    TextureInfo m_textureInfo;
};
}
#endif	/* TEXTURE_H */

