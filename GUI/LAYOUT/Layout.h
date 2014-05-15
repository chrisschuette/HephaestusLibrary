/* 
 * File:   Layout.h
 * Author: chris
 *
 * Created on February 9, 2014, 4:45 PM
 */

#ifndef LAYOUT_H
#define	LAYOUT_H

#include "../../LOG/Source.h"
#include <string>

namespace GUI {
    class Container;
    namespace LAYOUT {

        class Layout: public LOG::Source {
        public:
            Layout(std::string name);
            virtual ~Layout();
            virtual void layoutContainer(Container& container) = 0;
        private:

        };
    }
}
#endif	/* LAYOUT_H */

