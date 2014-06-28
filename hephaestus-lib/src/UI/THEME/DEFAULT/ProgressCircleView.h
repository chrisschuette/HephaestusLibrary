/* 
 * File:   ProgressCircleView.h
 * Author: chris
 *
 * Created on June 10, 2014, 11:07 PM
 */

#ifndef PROGRESSCIRCLEVIEW_H
#define	PROGRESSCIRCLEVIEW_H

#include "../../ComponentView.h"

namespace REND {
    class Renderable;
    class UniformSetting;
}

namespace UI {
    class Context;
    namespace THEME {
        namespace DEFAULT {

            class ProgressCircleView : public ComponentView {
            public:
                ProgressCircleView();
                virtual ~ProgressCircleView();

                // ComponentView
                virtual void render(REND::Renderer& renderer, const Component& component);
                virtual void update(Component& component);

                static ComponentView* create(Component& cmp, Context& ctx);


            private:
                REND::Renderable* m_backgroundRenderable;
                REND::UniformSetting* m_backgroundColor;

                REND::Renderable* m_circleRenderable;
                REND::UniformSetting* m_circleColor;

            };
        }
    }
}
#endif	/* PROGRESSCIRCLEVIEW_H */

