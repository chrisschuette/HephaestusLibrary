/* 
 * File:   VisualInstance.h
 * Author: chris
 *
 * Created on June 23, 2013, 5:51 PM
 */

#ifndef VISUALINSTANCE_H
#define	VISUALINSTANCE_H

namespace REND {
    class Renderer;
}

namespace VISUAL {
    class Visual;
    class VisualInstance {
    public:
        VisualInstance(const Visual& visual);
        virtual void render(REND::Renderer& renderer) const;
        virtual ~VisualInstance();
    private:
        const Visual& m_visual;
    };
}
#endif	/* VISUALINSTANCE_H */

