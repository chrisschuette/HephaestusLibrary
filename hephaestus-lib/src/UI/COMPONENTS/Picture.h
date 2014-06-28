/* 
 * File:   Picture.h
 * Author: chris
 *
 * Created on June 12, 2014, 12:17 PM
 */

#ifndef PICTURE_H
#define	PICTURE_H

#include "../Component.h"

namespace UI {
    namespace COMPONENTS {

        class Picture: public Component {
        public:
            Picture(std::string textureName);
            virtual ~Picture();
        private:
            std::string m_textureName;
        };
    }
}
#endif	/* PICTURE_H */

