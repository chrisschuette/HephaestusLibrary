/* 
 * File:   GLTextureAtlas.cpp
 * Author: chris
 * 
 * Created on February 6, 2014, 8:32 PM
 */

#include "GLTextureAtlas.h"
#include "../ERR/ERR.h"
#include <assert.h>

#include <GL/glew.h>

namespace GL {

    GLTextureAtlas::GLTextureAtlas(const size_t width, const size_t height, const size_t depth) : LOG::Source("GLTextureAtlas") {
        // We want a one pixel border around the whole atlas to avoid any artefact when
        // sampling texture
        MATH::ivec3 node = {
            {1, 1, width - 2}
        };

        assert((depth == 1) || (depth == 3) || (depth == 4));
        m_nodes = new MEM::Vector(sizeof (MATH::ivec3));
        m_used = 0;
        m_width = width;
        m_height = height;
        m_depth = depth;
        m_id = 0;

        m_nodes->push_back(&node);

        // value initialisation: initilises with 0's
        m_data = new unsigned char[width * height * depth]();

        if (m_data == NULL) {
            L(error) << "No more memory for allocating data";
            THROWS("ALLOCATION FAILURE");
        }

    }

    GLTextureAtlas::~GLTextureAtlas() {
        delete m_nodes;
        if (m_data)
            delete [] m_data;
        if (m_id)
            glDeleteTextures(1, &m_id);
    }

    void GLTextureAtlas::upload() {
        assert(m_data);

        if (!m_id) {
            glGenTextures(1, &m_id);
        }

        L(normal) << "texture name: " << m_id;

        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        if (m_depth == 4) {
#ifdef GL_UNSIGNED_INT_8_8_8_8_REV
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height,
                    0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, m_data);
#else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, self->width, self->height,
                    0, GL_RGBA, GL_UNSIGNED_BYTE, self->data);
#endif
        } else if (m_depth == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height,
                    0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height,
                    0, GL_RED, GL_UNSIGNED_BYTE, m_data);
        }
    }

    void GLTextureAtlas::clear() {
        MATH::ivec3 node = {
            {1, 1, 1}
        };

        assert(m_data);

        m_nodes->clear();
        m_used = 0;
        // We want a one pixel border around the whole atlas to avoid any artefact when
        // sampling texture
        node.z = m_width - 2;

        m_nodes->push_back(&node);
        memset(m_data, 0, m_width * m_height * m_depth);
    }

    void GLTextureAtlas::merge() {
        MATH::ivec3 *node, *next;
        size_t i;

        for (i = 0; i < m_nodes->size() - 1; ++i) {
            node = (MATH::ivec3 *) (m_nodes->get(i));
            next = (MATH::ivec3 *) (m_nodes->get(i + 1));
            if (node->y == next->y) {
                node->z += next->z;
                m_nodes->erase(i + 1);
                --i;
            }
        }
    }

    int GLTextureAtlas::fit(const size_t index, const size_t width, const size_t height) {
        MATH::ivec3 *node;
        int x, y, width_left;
        size_t i;

        node = (MATH::ivec3 *) (m_nodes->get(index));
        x = node->x;
        y = node->y;
        width_left = width;
        i = index;

        if ((x + width) > (m_width - 1)) {
            return -1;
        }
        y = node->y;
        while (width_left > 0) {
            node = (MATH::ivec3 *) (m_nodes->get(i));
            if (node->y > y) {
                y = node->y;
            }
            if ((y + height) > (m_height - 1)) {
                return -1;
            }
            width_left -= node->z;
            ++i;
        }
        return y;
    }

    void GLTextureAtlas::set_region(const size_t x,
            const size_t y,
            const size_t width,
            const size_t height,
            const unsigned char * data,
            const size_t stride) {
        size_t i;
        size_t depth;
        size_t charsize;

        assert(x > 0);
        assert(y > 0);
        assert(x < (m_width - 1));
        assert((x + width) <= (m_width - 1));
        assert(y < (m_height - 1));
        assert((y + height) <= (m_height - 1));

        depth = m_depth;
        charsize = sizeof (char);
        for (i = 0; i < height; ++i) {
            memcpy(m_data + ((y + i) * m_width + x) * charsize * depth,
                    data + (i * stride) * charsize, width * charsize * depth);
        }
    }

    MATH::ivec4
    GLTextureAtlas::get_region(const size_t width,
            const size_t height) {

        int y, best_height, best_width, best_index;
        MATH::ivec3 *node, *prev;
        MATH::ivec4 region = {
            {0, 0, width, height}};
        size_t i;

        best_height = INT_MAX;
        best_index = -1;
        best_width = INT_MAX;
        for (i = 0; i < m_nodes->size(); ++i) {
            y = fit(i,width,height);
            if (y >= 0) {
                node = (MATH::ivec3 *) m_nodes->get(i);
                if (((y + height) < best_height) ||
                        (((y + height) == best_height) && (node->z < best_width))) {
                    best_height = y + height;
                    best_index = i;
                    best_width = node->z;
                    region.x = node->x;
                    region.y = y;
                }
            }
        }

        if (best_index == -1) {
            region.x = -1;
            region.y = -1;
            region.width = 0;
            region.height = 0;
            return region;
        }

        node = (MATH::ivec3 *) malloc(sizeof (MATH::ivec3));
        if (node == NULL) {
            L(error) <<
                    "No more memory for allocating data";
            THROWS("Allocation failed.");
        }
        node->x = region.x;
        node->y = region.y + height;
        node->z = width;
        m_nodes->insert(best_index, node);
        free(node);

        for (i = best_index + 1; i < m_nodes->size(); ++i) {
            node = (MATH::ivec3 *) m_nodes->get(i);
            prev = (MATH::ivec3 *) m_nodes->get(i-1);

            if (node->x < (prev->x + prev->z)) {
                int shrink = prev->x + prev->z - node->x;
                node->x += shrink;
                node->z -= shrink;
                if (node->z <= 0) {
                    m_nodes->erase(i);
                    --i;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
        merge();
        m_used += width * height;
        return region;
    }

}
