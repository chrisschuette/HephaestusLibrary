/* 
 * File:   Uniform.h
 * Author: chris
 *
 * Created on June 1, 2014, 7:32 PM
 */

#ifndef GLUNIFORM_H
#define	GLUNIFORM_H

#include "../REND/Uniform.h"
#include "UniformSetting.h"
#include "GLShaderProgram.h"
#include "../ERR/ERR.h"
#include <GL/glew.h>
#include <iostream>

namespace GL {
    template <int N, typename T, char S>
    class Uniform : public REND::Uniform {
    public:
        Uniform(std::string name, REND::ShaderProgram& shaderProgram, GLint uniformLocation) : REND::Uniform(name, shaderProgram), m_uniformLocation(uniformLocation) {

        }
        GLint getUniformLocation() const { return m_uniformLocation; }
        virtual ~Uniform() {}
        virtual REND::UniformSetting* createUniformSetting(bool allocate) const {
            return new GL::UniformSetting<N,T,S>(*this, allocate);
        }
    private:
        GLint m_uniformLocation;
    };
    
    
}
#endif	/* GLUNIFORM_H */

