/* 
 * File:   GLShaderManager.cpp
 * Author: chris
 * 
 * Created on February 10, 2014, 6:01 PM
 */

#include "GLShaderManager.h"
#include "GLShader.h"
#include "GLShaderProgram.h"

namespace GL {
    GLShaderManager::GLShaderManager() : REND::ShaderManager(), LOG::Source("GLShaderManager") {
    }

    GLShaderManager::~GLShaderManager() {
    }

    bool GLShaderManager::addShaderPairFromFile(std::string name, std::string vertexShaderFile, std::string fragmentShaderFile) {
        GLShader vertexShader(GLShader::VERTEX);
        vertexShader.compileFromFile(vertexShaderFile);
        
        GLShader fragmentShader(GLShader::FRAGMENT);
        fragmentShader.compileFromFile(fragmentShaderFile);
        
        GLShaderProgram* shaderProgram = new GLShaderProgram(name);
        
        shaderProgram->attachShader(vertexShader);
        shaderProgram->attachShader(fragmentShader);
        shaderProgram->link();
                
        bool success = REND::ShaderManager::addShaderProgram(shaderProgram);
        
        if(success)
            L(normal) << "ShaderProgram " << name << " successfully loaded.";
        else
            L(error) << "ShaderProgram " << name << " failed to load.";
        return success;
    }
    
    void GLShaderManager::showInfo() {
        L(normal) << "========";
        L(normal) << "SHADERS:";
        L(normal) << "========";
                for(tShaderMap::iterator i = m_shaderMap.begin(), e = m_shaderMap.end();
                i != e; ++i) {
                    GL::GLShaderProgram* program = static_cast<GL::GLShaderProgram*>((*i).second);
                    L(normal) << "NAME: " << (*i).first;
                    if(program) {
                        GLint linkStatus;
                        glGetProgramiv(program->getProgram(),GL_LINK_STATUS,&linkStatus);
                        L(normal) << "link status: " << (linkStatus?"linked":"not linked");
                        GLint validateStatus;
                        glGetProgramiv(program->getProgram(),GL_VALIDATE_STATUS,&validateStatus);
                        L(normal) << "validation status: " << (validateStatus?"valid":"not valid");
                        GLint attachedShaders;
                        glGetProgramiv(program->getProgram(),GL_ATTACHED_SHADERS,&attachedShaders);
                        L(normal) << "attached shaders: " << attachedShaders;
                        GLint uniformCount;
                        glGetProgramiv(program->getProgram(),GL_ACTIVE_UNIFORMS,&uniformCount);
                        L(normal) << "uniform count: " << uniformCount;
                        GLint attributeCount;
                        glGetProgramiv(program->getProgram(),GL_ACTIVE_ATTRIBUTES,&attributeCount);
                        L(normal) << "attribute count: " << attributeCount;
                        GLint binarySize;
                        glGetProgramiv(program->getProgram(),GL_PROGRAM_BINARY_LENGTH,&binarySize);
                        L(normal) << "program size: " << binarySize << " bytes";
                        L(normal);
                    }
                    else
                        L(normal) << "FAILED.";
                }
     L(normal) << "========";
     L(normal);
    }
}
