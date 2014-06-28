/* 
 * File:   ShaderProgram.h
 * Author: chris
 *
 * Created on February 10, 2014, 5:46 PM
 */

#ifndef SHADERPROGRAM_H
#define	SHADERPROGRAM_H

#include "../SYS/IsReferenceCounted.h"
#include <string>
#include <map>

namespace REND {
    class Uniform;
    class UniformSetting;
    class ShaderProgram: public SYS::IsReferenceCounted<ShaderProgram> {
    public:
        ShaderProgram(std::string name, MEM::Pool<SYS::Reference<ShaderProgram> >& referencePool);
        virtual ~ShaderProgram();
        
        void addUniform(Uniform* uniform);
//        void addUniformSetting(UniformSetting* uniformSetting);
        
        UniformSetting* createUniformSetting(std::string name, bool allocate) const;
        
        virtual void activate() const = 0;
        const std::string& getProgramName() const { return m_name; }
    private:
        std::string m_name;
        std::map<std::string, Uniform*> m_uniforms;
//        std::map<std::string, UniformSetting*> m_uniformSettings;
    };
}
#endif	/* SHADERPROGRAM_H */

