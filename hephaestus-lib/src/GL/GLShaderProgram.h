/* 
 * File:   GLShaderProgram.h
 * Author: chris
 *
 * Created on February 6, 2014, 9:49 AM
 */

#ifndef GLSHADERPROGRAM_H
#define	GLSHADERPROGRAM_H

#include "../REND/ShaderProgram.h"
#include "UniformDescription.h"
#include "Uniform.h"

#include <GL/glew.h>
#include <string>
#include "../MATH/math3d.h"

namespace GL {
    class GLShader;

    class GLShaderProgram : public REND::ShaderProgram {
    public:
        GLShaderProgram(std::string name, MEM::Pool<SYS::Reference<ShaderProgram> >& referencePool);
        virtual ~GLShaderProgram();

        void attachShader(const GLShader& shader);
        void bindAttribute(int index, std::string name);
        void link();
        virtual void activate() const;

        GLuint getProgram() const {
            return m_hProgram;
        }
        void setUniformi(std::string name, int v) const;
        void setUniform(std::string name, const M3DMatrix44f& v) const;
        void setUniformf(std::string name, float v) const;
        void setUniformf(std::string name, float v1, float v2, float v3, float v4) const;
        void setUniform1iv(std::string name, int * value, int N) const;

        // UniformDescriptions

        template <int N, typename T, char S>
        GLShaderProgram& operator <<(const UniformDescription<N, T, S>& description) {
            GLint location = glGetUniformLocation(this->getProgram(), description.getName().c_str());
            if(location != -1) {
                Uniform<N,T,S>* u = new Uniform<N,T,S>(description.getName(), *this, location);
                this->addUniform(u);
            } else 
                THROWS("Unknown uniform " + description.getName());
            return *this;
        }

    private:
        GLuint m_hProgram;
    };
}
#endif	/* GLSHADERPROGRAM_H */

