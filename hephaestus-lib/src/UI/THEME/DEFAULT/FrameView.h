/* 
 * File:   FrameView.h
 * Author: chris
 *
 * Created on May 23, 2014, 9:34 PM
 */

#ifndef FRAMEVIEW_H
#define	FRAMEVIEW_H

#include "../../ComponentView.h"

namespace REND {
    class Renderer;
    class Renderable;
    class UniformSetting;
}

namespace UI {
    class Component;
    class Context;
    namespace THEME {
        namespace DEFAULT {

            class FrameView : public ComponentView {
            public:
                FrameView();
                virtual ~FrameView();
                virtual void update(Component& component);
                // ComponentView

                virtual void render(REND::Renderer& renderer, const Component& component);

                static ComponentView* create(Component& cmp, Context& ctx);
            private:
                REND::Renderable* m_background;
                REND::UniformSetting* m_backgroundColor;
            };
        }
    }
}
#endif	/* FRAMEVIEW_H */

