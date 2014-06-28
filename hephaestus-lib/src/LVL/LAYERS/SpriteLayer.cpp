/* 
 * File:   SpriteLayer.cpp
 * Author: chris
 * 
 * Created on June 18, 2014, 2:01 PM
 */

#include "SpriteLayer.h"

namespace LVL {
    namespace LAYERS {

        SpriteLayer::SpriteLayer(LVL::Context& ctx) : LVL::Layer(ctx) {
            setScrollFactor(1,1);
        }

        SpriteLayer::~SpriteLayer() {
        }

        void SpriteLayer::update(unsigned long int time, unsigned long int diff) {
            
        }
        
        void SpriteLayer::render(REND::Renderer& renderer, LVL::Context& context) {
            for( std::list<REND::SpriteInstance*>::iterator i = m_spriteInstances.begin(), e = m_spriteInstances.end(); i != e; ++i ) {
                REND::SpriteInstance* spriteInstance = (*i);
                spriteInstance->render(renderer);
            }
                
        }

        void SpriteLayer::addSpriteInstance(REND::SpriteInstance* spriteInstance) {
            m_spriteInstances.push_back(spriteInstance);
        }

    }
}
