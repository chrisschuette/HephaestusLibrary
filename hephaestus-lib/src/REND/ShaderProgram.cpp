/* 
 * File:   ShaderProgram.cpp
 * Author: chris
 * 
 * Created on February 10, 2014, 5:46 PM
 */

#include "ShaderProgram.h"
#include "../LOG/Core.h"
#include "Uniform.h"
#include "UniformSetting.h"

#define NAME "ShaderProgram"

namespace REND {

    ShaderProgram::ShaderProgram(std::string name, MEM::Pool<SYS::Reference<ShaderProgram> >& referencePool) : SYS::IsReferenceCounted<ShaderProgram>(referencePool), m_name(name) {
    }

    ShaderProgram::~ShaderProgram() {
        for (std::map<std::string, Uniform*>::iterator i = m_uniforms.begin(), e = m_uniforms.end(); i != e; ++i)
            delete (*i).second;
    }

    void ShaderProgram::addUniform(Uniform* uniform) {
        std::pair < std::map<std::string, Uniform*>::iterator, bool> r;
        r = m_uniforms.insert(std::pair<std::string, Uniform*>(uniform->getName(), uniform));
        if (r.second == false) {
            L(error) << "Failed to add uniform " << uniform->getName();
        }
    }
/*
    void ShaderProgram::addUniformSetting(UniformSetting* uniformSetting) {
        std::pair < std::map<std::string, UniformSetting*>::iterator, bool> r;
        r = m_uniformSettings.insert(std::pair<std::string, UniformSetting*>(uniformSetting->getUniform().getName(), uniformSetting));
        if (r.second == false) {
            L(error) << "Failed to add uniform " << uniformSetting->getUniform().getName();
        }
    }
*/
    UniformSetting* ShaderProgram::createUniformSetting(std::string name, bool allocate) const {
        //find the corresponding uniform
        std::map<std::string, Uniform*>::const_iterator it;
        it = m_uniforms.find(name);
        if (it != m_uniforms.end()) { //found
            return (*it).second->createUniformSetting(allocate);
        } else {//not found
            L(error) << "Failed to create UniformSetting " << name << " for shader " << m_name;
            return 0;
        }
    }

}
