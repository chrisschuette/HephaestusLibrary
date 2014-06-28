/* 
 * File:   PictureView.h
 * Author: chris
 *
 * Created on June 12, 2014, 12:20 PM
 */

#ifndef PICTUREVIEW_H
#define	PICTUREVIEW_H

#include "../../ComponentView.h"
#include "../../../SYS/Handle.h"
#include "../../../REND/Texture.h"

namespace REND {
    class Renderable;
    class UniformSetting;
}

namespace UI {
    class Context;
    namespace THEME {
        namespace DEFAULT {

            class PictureView : public ComponentView {
            public:
                PictureView();
                virtual ~PictureView();

                virtual void update(Component& component);
                virtual void render(REND::Renderer& renderer, const Component& component);
                static ComponentView* create(Component& cmp, Context& ctx);
            private:
                REND::Renderable* m_background;
                REND::UniformSetting* m_backgroundColor;

                REND::Renderable* m_picture;
                REND::UniformSetting* m_sprite;
                SYS::Handle<REND::Texture>* m_textureHandle;
            };
        }
    }
}
#endif	/* PICTUREVIEW_H */

