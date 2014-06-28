/* 
 * File:   Picture.cpp
 * Author: chris
 * 
 * Created on June 12, 2014, 12:17 PM
 */

#include "Picture.h"

namespace UI {
    namespace COMPONENTS {

        Picture::Picture(std::string textureName)
        : Component("Picture")
        , m_textureName(textureName) {
            setSizeBehaviour(FIXED,FIXED);
        }

        Picture::~Picture() {
        }

    }
}
