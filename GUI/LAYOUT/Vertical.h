/* 
 * File:   Vertical.h
 * Author: chris
 *
 * Created on February 9, 2014, 4:58 PM
 */

#ifndef VERTICAL_H
#define	VERTICAL_H

#include "Layout.h"

namespace GUI {
    namespace LAYOUT {

        class Vertical : public Layout {
        public:
            Vertical();
            virtual ~Vertical();
            virtual void layoutContainer(Container& container);
        private:

        };
    }
}
#endif	/* VERTICAL_H */

