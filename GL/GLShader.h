/* 
 * File:   GLShader.h
 * Author: chris
 *
 * Created on February 5, 2014, 11:41 PM
 */

#ifndef GLSHADER_H
#define	GLSHADER_H

#include "../LOG/Source.h"

#include <GL/glew.h>
#include <string>

namespace GL {
    class GLShader: public LOG::Source {
    public:
        enum TYPE { VERTEX, FRAGMENT, GEOMETRY };
    public:
        GLShader(TYPE shaderType);
        virtual ~GLShader();
        void compileFromString(std::string source);
        void compileFromFile(std::string filename);
        GLuint getShader() const { return m_hShader; }
    private:
        GLuint m_hShader;
    };
}
#endif	/* GLSHADER_H */

