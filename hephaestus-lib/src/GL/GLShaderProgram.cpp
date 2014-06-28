/* 
 * File:   GLShaderProgram.cpp
 * Author: chris
 * 
 * Created on February 6, 2014, 9:49 AM
 */

#include "GLShaderProgram.h"
#include "GLShader.h"
#include "../ERR/ERR.h"
#include "../LOG/Core.h"

#define NAME "GLShaderProgram"

namespace GL {

    GLShaderProgram::GLShaderProgram(std::string name, MEM::Pool<SYS::Reference<ShaderProgram> >& referencePool) : REND::ShaderProgram(name, referencePool) {
        m_hProgram = glCreateProgram();
    }

    GLShaderProgram::~GLShaderProgram() {
        glDeleteProgram(m_hProgram);
    }

    void GLShaderProgram::attachShader(const GLShader& shader) {
        glAttachShader(m_hProgram, shader.getShader());
    }

    void GLShaderProgram::bindAttribute(int index, std::string name) {
        glBindAttribLocation(m_hProgram, index, name.c_str());
    }

    void GLShaderProgram::link() {
        glLinkProgram(m_hProgram);

        GLint testVal;

        // Make sure link worked too
        glGetProgramiv(m_hProgram, GL_LINK_STATUS, &testVal);
        if (testVal == GL_FALSE) {
            char infoLog[1024];
            glGetProgramInfoLog(m_hProgram, 1024, NULL, infoLog);
            L(error) << "Unable to link program.";
            L(error) << infoLog;
            glDeleteProgram(m_hProgram);
            THROWS("Link failed.");
        } else
            L(normal) << "Shader link success.";
    }

    void GLShaderProgram::activate() const {
        glUseProgram(m_hProgram);
    }

    void GLShaderProgram::setUniformi(std::string name, int v) const {
        glUniform1i(glGetUniformLocation(m_hProgram, name.c_str()), v);
    }

    void GLShaderProgram::setUniform(std::string name, const M3DMatrix44f& v) const {
        glUniformMatrix4fv(glGetUniformLocation(m_hProgram, name.c_str()),
                1, 0, v);
    }

    void GLShaderProgram::setUniformf(std::string name, float v) const {
        glUniform1f(glGetUniformLocation(m_hProgram, name.c_str()), v);
    }

    void GLShaderProgram::setUniformf(std::string name, float v1, float v2, float v3, float v4) const {
        glUniform4f(glGetUniformLocation(m_hProgram, name.c_str()), v1, v2, v3, v4);
    }

    void GLShaderProgram::setUniform1iv(std::string name, int * value, int N) const {
        glUniform1iv(glGetUniformLocation(m_hProgram, name.c_str()), N, value);
    }

}
