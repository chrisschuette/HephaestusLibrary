/* 
 * File:   GLShader.cpp
 * Author: chris
 * 
 * Created on February 5, 2014, 11:41 PM
 */

#include "GLShader.h"
#include "../ERR/ERR.h"
#include "../LOG/Core.h"

#include <string>
#include <fstream>

#define NAME "GLShader"

namespace GL {

    GLShader::GLShader(TYPE shaderType) {
        switch (shaderType) {
            case VERTEX:
                m_hShader = glCreateShader(GL_VERTEX_SHADER);
                break;
            case FRAGMENT:
                m_hShader = glCreateShader(GL_FRAGMENT_SHADER);
                break;
            default:
                THROWS("Unknown shader type");
        }
    }

    GLShader::~GLShader() {
        glDeleteShader(m_hShader);
    }

    void GLShader::compileFromString(std::string source) {
        // upload source code
        GLchar * fsStringPtr[1];
        fsStringPtr[0] = (GLchar *) source.c_str();
        glShaderSource(m_hShader, 1, (const GLchar **) fsStringPtr, NULL);

        // compile the shader
        glCompileShader(m_hShader);

        // check for errors
        GLint testVal;
        glGetShaderiv(m_hShader, GL_COMPILE_STATUS, &testVal);
        if (testVal == GL_FALSE) {
            char infoLog[1024];
            glGetShaderInfoLog(m_hShader, 1024, NULL, infoLog);
            L(error) << "Unable to compile vertex shader source:";
            L(error) << infoLog;
            THROWS("Compile failed.");

        } else
            L(normal) << "Shader compile success.";
    }

    void GLShader::compileFromFile(std::string filename) {
        L(normal) << "Compiling " + filename + "...";
        std::ifstream sourceFile(filename.c_str());
        if (!sourceFile.is_open()) {
            L(error) << "Unable to open shader source file " << filename;
            THROWS("Unable to open file");
        }
        std::string source;
        sourceFile.seekg(0, std::ios::end);
        source.resize(sourceFile.tellg());
        sourceFile.seekg(0, std::ios::beg);
        sourceFile.read(&source[0], source.size());
        sourceFile.close();
        try {
        compileFromString(source);
        } catch (const ERR::Exception& e) {
            L(error) << "Unable to compile shader: " << filename;
            THROWS("Compile failed.");
        }
    }


}
