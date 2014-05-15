/* 
 * File:   Default.cpp
 * Author: chris
 * 
 * Created on February 10, 2014, 12:18 AM
 */

#include "Default.h"
#include "../../UTIL/hash.h"
#include "DEFAULT/ButtonView.h"

namespace GUI {
    namespace THEMES {
        Default::Default() : GUI::Theme("Default") {
            registerCreator(TypeID(UTIL::hash("Button")),&DEFAULT::ButtonView::create);
        }

        Default::~Default() {
        }
    }
}
