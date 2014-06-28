/* 
 * File:   GLVertexBuffer.h
 * Author: chris
 *
 * Created on February 3, 2014, 10:13 PM
 */

#ifndef GLVERTEXBUFFER_H
#define	GLVERTEXBUFFER_H

#include "../MEM/Vector.h"
#include "../REND/RenderBuffer.h"
#include "GLVertexAttribute.h"
#include <string>
#include <GL/glew.h> 

#define GLVertexBuffer_USE_VAO

namespace GL {
    class GLVertexAttribute;

    namespace GLVertexBuffer_CONST {
        const int MAX_VERTEX_ATTRIBUTE = 16;
    }

    class GLVertexBuffer: public REND::RenderBuffer {
    public:
        GLVertexBuffer(std::string format);
        virtual ~GLVertexBuffer();

        // data management
        size_t push_back(const void * vertices, const size_t vcount, const GLuint * indices, const size_t icount);
        size_t insert(size_t index, const void * vertices, const size_t vcount, const GLuint * indices, const size_t icount);
        void push_back_vertices(const void * vertices, const size_t vcount);
        void push_back_indices(const GLuint * indices, const size_t icount);
        void update_vertex(const void * vertex, int index);
        void upload();

        //rendering
        void render_setup(GLenum mode);
        void render(GLenum mode);
        void render_finish();

        virtual void draw();


    private:
#ifdef GLVertexBuffer_USE_VAO
        /** GL identity of the Vertex Array Object */
        GLuint m_VAO_id;
#endif
        /** Format of the vertex buffer. */
        std::string m_format;

        /** Vector of vertices. */
        MEM::Vector * m_vertices;

        /** GL identity of the vertices buffer. */
        GLuint m_vertices_id;

        /** Vector of indices. */
        MEM::Vector * m_indices;

        /** GL identity of the indices buffer. */
        GLuint m_indices_id;

        /** Current size of the vertices buffer in GPU */
        size_t m_GPU_vsize;

        /** Current size of the indices buffer in GPU*/
        size_t m_GPU_isize;

        /** GL primitives to render. */
        GLenum m_mode;

        /** Whether the vertex buffer needs to be uploaded to GPU memory. */
        char m_state;

        /** Individual items */
        MEM::Vector * m_items;

        /** Array of attributes. */
        GLVertexAttribute *m_attributes[GLVertexBuffer_CONST::MAX_VERTEX_ATTRIBUTE];
    };
}
#endif	/* GLVERTEXBUFFER_H */

