/* 
 * File:   Camera.h
 * Author: chris
 *
 * Created on May 27, 2014, 12:22 PM
 */

#ifndef CAMERA_H
#define	CAMERA_H

#include "../MATH/vec234.h"

namespace REND {

    class Camera {
    public:
        Camera();
        virtual ~Camera();
    
        virtual void translateLocal(float dx, float dy, float dz) = 0;
        virtual const MATH::vec3& getPosition() = 0; 
    private:

    };
}
#endif	/* CAMERA_H */

