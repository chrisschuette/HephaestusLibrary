/* 
 * File:   Context.h
 * Author: chris
 *
 * Created on February 9, 2014, 5:24 PM
 */

#ifndef GUI_CONTEXT_H
#define	GUI_CONTEXT_H

#include "../VIEW/Context.h"

namespace GUI {
    class Renderer;
    class Context: public VIEW::Context {
    public:
        Context();
        virtual ~Context();
        virtual Renderer& getRenderer()=0;
    private:
    };
}
#endif	/* GUI_CONTEXT_H */

