/* 
 * File:   Uniform.cpp
 * Author: chris
 * 
 * Created on June 1, 2014, 5:58 PM
 */

#include "Uniform.h"

namespace REND {

    Uniform::Uniform(std::string name, ShaderProgram& shaderProgram) : m_name(name), m_shaderProgram(shaderProgram) {
    }

    Uniform::~Uniform() {
    }
}
