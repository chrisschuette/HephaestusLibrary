/* 
 * File:   ShaderProgramInstance.cpp
 * Author: chris
 * 
 * Created on June 2, 2014, 12:30 AM
 */

#include "ShaderProgramInstance.h"

namespace REND {

    ShaderProgramInstance::ShaderProgramInstance(const SYS::Handle<REND::ShaderProgram>& handle) : SYS::Handle<REND::ShaderProgram>(handle) {
    }

    ShaderProgramInstance::~ShaderProgramInstance() {
    }

    UniformSetting* ShaderProgramInstance::createUniformSetting(std::string name, bool allocate) const {
        const REND::ShaderProgram* shaderProgram = this->operator *();
        return shaderProgram->createUniformSetting(name, allocate);
    }

}
