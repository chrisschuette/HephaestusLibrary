/* 
 * File:   GLVertexAttribute.cpp
 * Author: chris
 * 
 * Created on February 3, 2014, 9:57 PM
 */

#include "GLVertexAttribute.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

namespace GL {

    GLVertexAttribute::GLVertexAttribute(std::string desc) : LOG::Source("GLVertexAttribute") {
        size_t pos = desc.find(':');
        assert((pos + 3 == desc.size()) || (pos + 4 == desc.size()));

        char ctype = desc.at(pos + 2);
        switch (ctype) {
            case 'b': m_type = GL_BYTE;
                break;
            case 'B': m_type = GL_UNSIGNED_BYTE;
                break;
            case 's': m_type = GL_SHORT;
                break;
            case 'S': m_type = GL_UNSIGNED_SHORT;
                break;
            case 'i': m_type = GL_INT;
                break;
            case 'I': m_type = GL_UNSIGNED_INT;
                break;
            case 'f': m_type = GL_FLOAT;
                break;
            default: m_type = 0;
                break;
        }

        if (pos + 4 == desc.size()) {
            if (desc.at(pos + 3) == 'n')
                m_normalized = true;
        } else
            m_normalized = false;


        m_name = desc.substr(0, pos);
        m_index = -1;
        m_size = desc.at(pos + 1) - '0';
        m_stride = 0;
        m_pointer = 0;
    }

    GLVertexAttribute::~GLVertexAttribute() {
    }
   
    void GLVertexAttribute::enable() {
        if (m_index == -1) {
            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);
            if (program == 0) {
                return;
            }
            m_index = glGetAttribLocation(program, m_name.c_str());
            if (m_index == -1) {
                return;
            }
        }
        glEnableVertexAttribArray(m_index);
        glVertexAttribPointer(m_index, m_size, m_type,
                m_normalized, m_stride, m_pointer);
    }

}