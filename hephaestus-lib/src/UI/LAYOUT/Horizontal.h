/* 
 * File:   Horizontal.h
 * Author: chris
 *
 * Created on February 9, 2014, 4:58 PM
 */

#ifndef UIHORIZONTAL_H
#define	UIHORIZONTAL_H

#include "Layout.h"

namespace UI {
    namespace LAYOUT {

        class Horizontal : public Layout {
        public:
            Horizontal();
            virtual ~Horizontal();
            virtual void layout(View& view, Context& context);
            void layoutOverflow(View& view, Context& context);
        private:

        };
    }
}
#endif	/* UIHORIZONTAL_H */

