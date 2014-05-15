/* 
 * File:   GLVertexBuffer.cpp
 * Author: chris
 * 
 * Created on February 3, 2014, 10:13 PM
 */

#include "GLVertexBuffer.h"
#include "../MEM/Vector.h"
#include "../MATH/vec234.h"

namespace GL {

    /**
     * Buffer status
     */
#define CLEAN  (0)
#define DIRTY  (1)
#define FROZEN (2)

    GLVertexBuffer::GLVertexBuffer(std::string format) : LOG::Source("GLVertexBuffer") {
        size_t i, index = 0, stride = 0;
        GLchar *pointer = 0;
        m_format = format;

        for (int i = 0; i < GLVertexBuffer_CONST::MAX_VERTEX_ATTRIBUTE; ++i) {
            m_attributes[i] = 0;
        }

        size_t pos = 0;
        size_t end;
        do {
            GLVertexAttribute* attribute;
            GLuint attribute_size = 0;
            end = format.find(',', pos);

            std::string desc;

            if (end == std::string::npos) { //not found
                desc = format.substr(pos);
            } else { //found
                desc = format.substr(pos, end - pos);
                pos = end + 1;
            }

            attribute = new GLVertexAttribute(desc);

            attribute->setPointer(pointer);

            switch (attribute->getType()) {
                case GL_BOOL: attribute_size = sizeof (GLboolean);
                    break;
                case GL_BYTE: attribute_size = sizeof (GLbyte);
                    break;
                case GL_UNSIGNED_BYTE: attribute_size = sizeof (GLubyte);
                    break;
                case GL_SHORT: attribute_size = sizeof (GLshort);
                    break;
                case GL_UNSIGNED_SHORT: attribute_size = sizeof (GLushort);
                    break;
                case GL_INT: attribute_size = sizeof (GLint);
                    break;
                case GL_UNSIGNED_INT: attribute_size = sizeof (GLuint);
                    break;
                case GL_FLOAT: attribute_size = sizeof (GLfloat);
                    break;
                default: attribute_size = 0;
            }
            stride += attribute->getSize() * attribute_size;
            pointer += attribute->getSize() * attribute_size;
            m_attributes[index] = attribute;
            index++;
        } while (end != std::string::npos);

        for (i = 0; i < index; ++i) {
            m_attributes[i]->setStride(stride);
        }

        m_vertices = new MEM::Vector(stride);
        m_vertices_id = 0;
        m_GPU_vsize = 0;

        m_indices = new MEM::Vector(sizeof (GLuint));
        m_indices_id = 0;
        m_GPU_isize = 0;

        m_items = new MEM::Vector(sizeof (MATH::ivec4));
        m_state = DIRTY;
        m_mode = GL_TRIANGLES;
    }

    GLVertexBuffer::~GLVertexBuffer() {
        for (int i = 0; i < GLVertexBuffer_CONST::MAX_VERTEX_ATTRIBUTE; ++i)
            if (m_attributes[i])
                delete m_attributes[i];

        delete m_vertices;
        m_vertices = 0;

        if (m_vertices_id)
            glDeleteBuffers(1, &m_vertices_id);
        m_vertices_id = 0;

        delete m_indices;
        m_indices = 0;

        if (m_indices_id)
            glDeleteBuffers(1, &m_indices_id);
        m_indices_id = 0;
    }

    size_t GLVertexBuffer::push_back(const void * vertices, const size_t vcount, const GLuint * indices, const size_t icount) {
        return insert(m_items->size(), vertices, vcount, indices, icount);
    }

    void GLVertexBuffer::push_back_vertices(const void * vertices, const size_t vcount) {
        m_state |= DIRTY;
        m_vertices->push_back_data(vertices, vcount);
    }

    void GLVertexBuffer::push_back_indices(const GLuint * indices, const size_t icount) {
        m_state |= DIRTY;
        m_indices->push_back_data(indices, icount);
    }

    void GLVertexBuffer::update_vertex(const void * vertex, int index ) {
        assert (vertex);
        m_state = FROZEN;
        m_vertices->set(index, vertex);
        m_state = DIRTY;

    }

    
    size_t GLVertexBuffer::insert(size_t index, const void * vertices, const size_t vcount, const GLuint * indices, const size_t icount) {
        size_t vstart, istart, i;
        MATH::ivec4 item;
        assert(vertices);
        assert(indices);

        m_state = FROZEN;

        // Push back vertices
        vstart = m_vertices->size();
        push_back_vertices(vertices, vcount);

        // Push back indices
        istart = m_indices->size();
        push_back_indices(indices, icount);
        // Update indices within the vertex buffer
        for (i = 0; i < icount; ++i) {
            *(GLuint *) m_indices->get(istart + i) += vstart;
        }

        // Insert item
        item.x = vstart;
        item.y = vcount;
        item.z = istart;
        item.w = icount;
        m_items->insert(index, &item);

        m_state = DIRTY;
        return index;
    }

    void GLVertexBuffer::upload() {
        size_t vsize, isize;

        if (m_state == FROZEN)
            return;

        if (!m_vertices_id)
            glGenBuffers(1, &m_vertices_id);

        if (!m_indices_id)
            glGenBuffers(1, &m_indices_id);

        vsize = m_vertices->size() * m_vertices->getItemSize();
        isize = m_indices->size() * m_indices->getItemSize();


        // Always upload vertices first such that indices do not point to non
        // existing data (if we get interrupted in between for example).

        // Upload vertices
        glBindBuffer(GL_ARRAY_BUFFER, m_vertices_id);
        if (vsize != m_GPU_vsize) {
            glBufferData(GL_ARRAY_BUFFER, vsize, m_vertices->getItemsPointer(), GL_DYNAMIC_DRAW);
            m_GPU_vsize = vsize;
        } else {
            glBufferSubData(GL_ARRAY_BUFFER, 0, vsize, m_vertices->getItemsPointer());
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Upload indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indices_id);
        if (isize != m_GPU_isize) {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                    isize, m_indices->getItemsPointer(), GL_DYNAMIC_DRAW);
            m_GPU_isize = isize;
        } else {
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
                    0, isize, m_indices->getItemsPointer());
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void GLVertexBuffer::render_setup(GLenum mode) {
        size_t i;

        if (m_state != CLEAN) {
            upload();
            m_state = CLEAN;
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_vertices_id);

        for (i = 0; i < GLVertexBuffer_CONST::MAX_VERTEX_ATTRIBUTE; ++i) {
            GLVertexAttribute *attribute = m_attributes[i];

            if (attribute == 0)
                continue;
            else
                attribute->enable();

        }

        if (m_indices->size()) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indices_id);
        }
        m_mode = mode;
    }

    void GLVertexBuffer::render(GLenum mode) {
        size_t vcount = m_vertices->size();
        size_t icount = m_indices->size();

        render_setup(mode);
        if (icount) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indices_id);
            glDrawElements(mode, icount, GL_UNSIGNED_INT, 0);
        } else {
            glDrawArrays(mode, 0, vcount);
        }
        render_finish();
    }

    void GLVertexBuffer::render_finish() {
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    }

}
