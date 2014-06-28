/* 
 * File:   Uniform.h
 * Author: chris
 *
 * Created on June 1, 2014, 5:58 PM
 */

#ifndef UNIFORM_H
#define	UNIFORM_H

#include <string>

namespace REND {
    class ShaderProgram;
    class UniformSetting;
    class Uniform {
    public:
        Uniform(std::string name, ShaderProgram& shaderProgram);
        virtual ~Uniform();
        
        const std::string& getName() const { return m_name; }
        ShaderProgram& getShaderProgram() const { return m_shaderProgram; }
        virtual UniformSetting* createUniformSetting(bool allocate) const = 0;
    protected:
        std::string m_name;
        ShaderProgram& m_shaderProgram;
    };
}
#endif	/* UNIFORM_H */

