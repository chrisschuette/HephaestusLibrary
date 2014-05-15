/* 
 * File:   ButtonView.h
 * Author: chris
 *
 * Created on February 10, 2014, 12:31 AM
 */

#ifndef BUTTONVIEW_H
#define	BUTTONVIEW_H

#include "../../ComponentView.h"
#include "../../../GL/GLVertexBuffer.h"
#include "../../../MATH/vec234.h"
#include "../../../LOG/Source.h"
#include <iostream>

namespace SYS {
    template <class T>
    class Handle;
}

namespace REND {
    namespace FONTS {
        class Font;
    }
}

namespace GL {
    class GLShaderProgram;
}

namespace GUI {
    class Component;
    class Context;
    namespace THEMES {
        namespace DEFAULT {

            class ButtonView : public ComponentView, public LOG::Source {
            public:
                ButtonView();
                virtual ~ButtonView();
                static ComponentView* create(Component& cmp, Context& ctx);
                virtual void render(const Component& component, VIEW::Context& pContext);
            private:
                const GL::GLShaderProgram* m_shaderProgram;
                const GL::GLShaderProgram* m_outlineProgram;
                GL::GLVertexBuffer* m_outline;
                GL::GLVertexBuffer* m_captionText;
                SYS::Handle<REND::FONTS::Font>* m_fontHandle;
            };
        }
    }
}
#endif	/* BUTTONVIEW_H */

