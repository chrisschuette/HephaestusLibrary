/* 
 * File:   Camera.cpp
 * Author: chris
 * 
 * Created on May 27, 2014, 12:23 PM
 */

#include "Camera.h"

namespace GL {

    Camera::Camera() : REND::Camera() {
        m_frame.SetForwardVector(0, 0, -1);
        m_frame.SetOrigin(0, 0, 0);
        m_frame.SetUpVector(0, 1, 0);

    }

    void Camera::translateLocal(float dx, float dy, float dz) {
        m_frame.TranslateLocal(dx, dy, dz);
    }

    const MATH::vec3& Camera::getPosition() {
        return reinterpret_cast<const MATH::vec3&>(*m_frame.GetOrigin());
    }

    Camera::~Camera() {
    }
}
