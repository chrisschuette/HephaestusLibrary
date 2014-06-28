/* 
 * File:   UniformSetting.cpp
 * Author: chris
 * 
 * Created on June 1, 2014, 7:03 PM
 */

#include "UniformSetting.h"
#include "Uniform.h"

namespace REND {

    UniformSetting::UniformSetting(const Uniform& uniform)
    : m_uniform(uniform) {

    }

    UniformSetting::~UniformSetting() {
    }
}
