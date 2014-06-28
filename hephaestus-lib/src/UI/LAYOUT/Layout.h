/* 
 * File:   Layout.h
 * Author: chris
 *
 * Created on May 23, 2014, 7:51 PM
 */

#ifndef LAYOUT_H
#define	LAYOUT_H

#include <string>

namespace UI {
    class View;
    class Context;
    namespace LAYOUT {

        class Layout {
        public:
            Layout(std::string name);
            virtual ~Layout();
            virtual void layout(View& view, Context& context) = 0;
        private:
            std::string m_name;
        };
    }
}
#endif	/* LAYOUT_H */

