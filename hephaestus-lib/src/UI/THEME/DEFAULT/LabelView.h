/* 
 * File:   LabelView.h
 * Author: chris
 *
 * Created on June 11, 2014, 10:58 PM
 */

#ifndef LABELVIEW_H
#define	LABELVIEW_H

#include "../../ComponentView.h"
#include "../../../SYS/Handle.h"
#include "../../../REND/FONTS/Font.h"
#include "../../../MATH/vec234.h"


namespace REND {
    class Renderable;
    class UniformSetting;
}

namespace UI {
    class Context;
    namespace THEME {
        namespace DEFAULT {

            class LabelView : public ComponentView {
            public:
                LabelView();
                virtual ~LabelView();
                virtual void update(Component& component);
                virtual void render(REND::Renderer& renderer, const Component& component);
                static ComponentView* create(Component& cmp, Context& ctx);
            private:
                REND::Renderable* m_background;
                REND::UniformSetting* m_backgroundColor;

                REND::Renderable* m_text;
                REND::UniformSetting* m_textColor;
                REND::UniformSetting* m_texture;
                SYS::Handle<REND::FONTS::Font>* m_fontHandle;
                MATH::vec2 m_textDimensions;
            };
        }
    }
}
#endif	/* LABELVIEW_H */

