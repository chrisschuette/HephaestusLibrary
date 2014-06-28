/* 
 * File:   Layer.h
 * Author: chris
 *
 * Created on May 27, 2014, 12:27 PM
 */

#ifndef LAYER_H
#define	LAYER_H

namespace REND {
    class Renderer;
}

namespace LVL {
    class Context;
    class Layer {
    public:
        Layer(Context& context);
        virtual ~Layer();
        virtual void update(unsigned long int time, unsigned long int diff) = 0;
        virtual void render(REND::Renderer& renderer, LVL::Context& context) = 0;
        void setScrollFactor(float scrollFactorX, float scrollFactorY) { m_scrollFactorX = scrollFactorX; m_scrollFactorY = scrollFactorY; }
        inline float getScrollFactorX() const { return m_scrollFactorX; }
        inline float getScrollFactorY() const { return m_scrollFactorY; }
    protected:
        Context& m_ctx;
        float m_scrollFactorX;
        float m_scrollFactorY;
    };
}
#endif	/* LAYER_H */

