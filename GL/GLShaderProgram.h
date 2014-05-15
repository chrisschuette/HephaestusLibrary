/* 
 * File:   GLShaderProgram.h
 * Author: chris
 *
 * Created on February 6, 2014, 9:49 AM
 */

#ifndef GLSHADERPROGRAM_H
#define	GLSHADERPROGRAM_H

#include "../LOG/Source.h"
#include "../REND/ShaderProgram.h"

#include <GL/glew.h>
#include <string>
#include "../MATH/math3d.h"

namespace GL {
    class GLShader;

    class GLShaderProgram : public REND::ShaderProgram, public LOG::Source {
    public:
        GLShaderProgram(std::string name);
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
    private:
        GLuint m_hProgram;
    };
}
#endif	/* GLSHADERPROGRAM_H */

