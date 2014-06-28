/* 
 * File:   Vertical.h
 * Author: chris
 *
 * Created on February 9, 2014, 4:58 PM
 */

#ifndef UIVERTICAL_H
#define	UIVERTICAL_H

#include "Layout.h"

namespace UI {
    namespace LAYOUT {

        class Vertical : public Layout {
        public:
            Vertical();
            virtual ~Vertical();
            virtual void layout(View& view, Context& context);
            void layoutOverflow(View& view, Context& context);
        private:

        };
    }
}
#endif	/* UIVERTICAL_H */

