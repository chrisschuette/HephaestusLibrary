/* 
 * File:   GLVertexAttribute.h
 * Author: chris
 *
 * Created on February 3, 2014, 9:57 PM
 */

#ifndef GLVERTEXATTRIBUTE_H
#define	GLVERTEXATTRIBUTE_H

#include <string>
#include <GL/glew.h>

#include "../LOG/Source.h"

namespace GL {

    class GLVertexAttribute: public LOG::Source {
    public:
        GLVertexAttribute(std::string desc);
        virtual ~GLVertexAttribute();
        
        inline void setPointer(GLvoid * pointer) { m_pointer = pointer; }
        inline GLenum getType() const { return m_type; }
        inline GLint getSize() const { return m_size; }
        inline void setStride(GLsizei stride) { m_stride = stride; }
        void enable();
    private:
        /**
         *  atribute name
         */
        std::string m_name;

        /**
         * index of the generic vertex attribute to be modified.
         */
        GLuint m_index;

        /**
         * Number of components per generic vertex attribute.
         *
         * Must be 1, 2, 3, or 4. The initial value is 4.
         */
        GLint m_size;

        /** 
         *  data type of each component in the array.
         *
         *  Symbolic constants GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT,
         *  GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_FLOAT, or GL_DOUBLE are
         *  accepted. The initial value is GL_FLOAT.
         */
        GLenum m_type;

        /**
         *  whether fixed-point data values should be normalized (GL_TRUE) or
         *  converted directly as fixed-point values (GL_FALSE) when they are
         *  accessed.
         */
        GLboolean m_normalized;

        /**
         *  byte offset between consecutive generic vertex attributes.
         *
         *  If stride is 0, the generic vertex attributes are understood to be
         *  tightly packed in the array. The initial value is 0.
         */
        GLsizei m_stride;

        /**
         *  pointer to the first component of the first attribute element in the
         *  array.
         */
        GLvoid * m_pointer;

        /**
         * pointer to the function that enable this attribute.
         */
        void ( * m_enable)(void *);
    };
}
#endif	/* GLVERTEXATTRIBUTE_H */

