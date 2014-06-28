/* 
 * File:   GLTextureAtlas.h
 * Author: chris
 *
 * Created on February 6, 2014, 8:32 PM
 */

#ifndef GLTEXTUREATLAS_H
#define	GLTEXTUREATLAS_H

#include "../MEM/Vector.h"
#include "../MATH/vec234.h"

namespace GL {

    class GLTextureAtlas {
    public:
        GLTextureAtlas(const size_t width, const size_t height, const size_t depth);
        virtual ~GLTextureAtlas();

        void upload();
        void clear();
        void merge();
        size_t getWidth() const { return m_width; }
        size_t getHeight() const { return m_height; }
        size_t getDepth() const { return m_depth; }
        int fit(const size_t index, const size_t width, const size_t height);
        void set_region(const size_t x,
                const size_t y,
                const size_t width,
                const size_t height,
                const unsigned char * data,
                const size_t stride);
        MATH::ivec4 get_region(const size_t width,
                const size_t height);
        unsigned int getTexture() const { return m_id; }
    private:
        /**
         * Allocated nodes
         */
        MEM::Vector * m_nodes;

        /**
         *  Width (in pixels) of the underlying texture
         */
        size_t m_width;

        /**
         * Height (in pixels) of the underlying texture
         */
        size_t m_height;

        /**
         * Depth (in bytes) of the underlying texture
         */
        size_t m_depth;

        /**
         * Allocated surface size
         */
        size_t m_used;

        /**
         * Texture identity (OpenGL)
         */
        unsigned int m_id;

        /**
         * Atlas data
         */
        unsigned char * m_data;
    };
}
#endif	/* GLTEXTUREATLAS_H */

