/* 
 * File:   UniformSetting.cpp
 * Author: chris
 * 
 * Created on June 1, 2014, 8:17 PM
 */

#include "UniformSetting.h"
#include "../LOG/Core.h"
#include "GLShaderProgram.h"
#include "Uniform.h"

#define NAME "UniformSetting"

namespace GL {
    template <>
    void UniformSetting<1, int, 'V'>::set() const {
        if (!m_data)
            THROWS("No data available");
        const GL::Uniform<1, int, 'V'>& u = static_cast<const GL::Uniform<1, int, 'V'>&> (m_uniform);
        GL::GLShaderProgram& program = static_cast<GL::GLShaderProgram&> (m_uniform.getShaderProgram());
        glUniform1i(u.getUniformLocation(), m_data[0]);
    }

    template <>
    void UniformSetting<1, int, 'V'>::set(const void* data) const {
        const GL::Uniform<1, int, 'V'>& u = static_cast<const GL::Uniform<1, int, 'V'>&> (m_uniform);
        const int* temp = (const int*) data;
        GL::GLShaderProgram& program = static_cast<GL::GLShaderProgram&> (m_uniform.getShaderProgram());
        glUniform1i(u.getUniformLocation(), *temp);
    }

    template <>
    void UniformSetting<1, float, 'V'>::set() const {
        if (!m_data)
            THROWS("No data available");
        const GL::Uniform<1, float, 'V'>& u = static_cast<const GL::Uniform<1, float, 'V'>&> (m_uniform);
        GL::GLShaderProgram& program = static_cast<GL::GLShaderProgram&> (m_uniform.getShaderProgram());
        glUniform1f(u.getUniformLocation(), m_data[0]);
    }

    template <>
    void UniformSetting<1, float, 'V'>::set(const void* data) const {
        const GL::Uniform<1, float, 'V'>& u = static_cast<const GL::Uniform<1, float, 'V'>&> (m_uniform);
        const int* temp = (const int*) data;
        GL::GLShaderProgram& program = static_cast<GL::GLShaderProgram&> (m_uniform.getShaderProgram());
        glUniform1f(u.getUniformLocation(), *temp);
    }

    template <>
    void UniformSetting<4, float, 'V'>::set() const {
        if (!m_data)
            THROWS("No data available");
        const GL::Uniform<4, float, 'V'>& u = static_cast<const GL::Uniform<4, float, 'V'>&> (m_uniform);
        GL::GLShaderProgram& program = static_cast<GL::GLShaderProgram&> (m_uniform.getShaderProgram());
        glUniform4f(u.getUniformLocation(), m_data[0], m_data[1], m_data[2], m_data[3]);
    }

    template <>
    void UniformSetting<4, float, 'V'>::set(const void* data) const {
        const GL::Uniform<4, float, 'V'>& u = static_cast<const GL::Uniform<4, float, 'V'>&> (m_uniform);
        const float* temp = (const float*) data;
        GL::GLShaderProgram& program = static_cast<GL::GLShaderProgram&> (m_uniform.getShaderProgram());
        glUniform4f(u.getUniformLocation(), temp[0], temp[1], temp[2], temp[3]);
    }

    template <>
    void UniformSetting<4, float, 'M'>::set() const {
        if (!m_data)
            THROWS("No data available");
        const GL::Uniform<4, float, 'M'>& u = static_cast<const GL::Uniform<4, float, 'M'>&> (m_uniform);
        GL::GLShaderProgram& program = static_cast<GL::GLShaderProgram&> (m_uniform.getShaderProgram());
        glUniformMatrix4fv(u.getUniformLocation(),
                1, 0, m_data);

    }

    template <>
    void UniformSetting<4, float, 'M'>::set(const void* data) const {
        const GL::Uniform<4, float, 'M'>& u = static_cast<const GL::Uniform<4, float, 'M'>&> (m_uniform);
        const float* temp = (const float*) data;
        GL::GLShaderProgram& program = static_cast<GL::GLShaderProgram&> (m_uniform.getShaderProgram());
        glUniformMatrix4fv(u.getUniformLocation(),
                1, 0, temp);
    }
}
