/* 
 * File:   Default.cpp
 * Author: chris
 * 
 * Created on May 23, 2014, 9:09 PM
 */

#include "Default.h"

// components
#include "DEFAULT/ButtonView.h"
#include "DEFAULT/FrameView.h"
#include "DEFAULT/ProgressCircleView.h"
#include "DEFAULT/LabelView.h"
#include "DEFAULT/PictureView.h"
#include "../../UTIL/hash.h"

namespace UI {
    namespace THEME {

        Default::Default() : Theme() {
            registerCreator(UTIL::hash("Button"), DEFAULT::ButtonView::create);
            registerCreator(UTIL::hash("Frame"), DEFAULT::FrameView::create);
            registerCreator(UTIL::hash("ProgressCircle"), DEFAULT::ProgressCircleView::create);
            registerCreator(UTIL::hash("Label"), DEFAULT::LabelView::create);
            registerCreator(UTIL::hash("Picture"), DEFAULT::PictureView::create);
        }

        Default::~Default() {
        }
    }
}
