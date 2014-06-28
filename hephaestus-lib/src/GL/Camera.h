/* 
 * File:   Camera.h
 * Author: chris
 *
 * Created on May 27, 2014, 12:23 PM
 */

#ifndef GLCAMERA_H
#define	GLCAMERA_H

#include "../REND/Camera.h"
#include "GLFrame.h"

namespace GL {

    class Camera : public REND::Camera {
    public:
        Camera();
        virtual ~Camera();

        virtual void translateLocal(float dx, float dy, float dz);
        virtual const MATH::vec3& getPosition(); 

        // getters & setters

        const GLFrame& getFrame() const {
            return m_frame;
        }
    private:
        GLFrame m_frame;
    };
}
#endif	/* GLCAMERA_H */

