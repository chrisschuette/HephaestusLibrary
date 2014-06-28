/* 
 * File:   SpriteLayer.h
 * Author: chris
 *
 * Created on June 18, 2014, 2:01 PM
 */

#ifndef SPRITELAYER_H
#define	SPRITELAYER_H

#include "../Layer.h"
#include "../../REND/SpriteInstance.h"
#include <list>

namespace LVL {
    namespace LAYERS {

        class SpriteLayer : public LVL::Layer {
        public:
            SpriteLayer(LVL::Context& ctx);
            virtual ~SpriteLayer();
            
            virtual void update(unsigned long int time, unsigned long int diff);
            virtual void render(REND::Renderer& renderer, LVL::Context& context);
            
            void addSpriteInstance(REND::SpriteInstance* spriteInstance);
        private:
            std::list<REND::SpriteInstance*> m_spriteInstances;
        };
    }
}
#endif	/* SPRITELAYER_H */

