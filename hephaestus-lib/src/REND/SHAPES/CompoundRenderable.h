/* 
 * File:   CompoundRenderable.h
 * Author: chris
 *
 * Created on June 3, 2014, 10:02 AM
 */

#ifndef COMPOUNDRENDERABLE_H
#define	COMPOUNDRENDERABLE_H

#include "../Renderable.h"

namespace GEOMETRY {
    class Compound;
}

namespace REND {
    namespace SHAPES {

        class CompoundRenderable: public REND::Renderable {
        public:
            CompoundRenderable(GEOMETRY::Compound* compound, RenderBuffer* renderBuffer, ShaderProgramInstance shaderInstance);
            virtual ~CompoundRenderable();
            
            const GEOMETRY::Compound* getCompound() const { return m_compound; }
        private:
            GEOMETRY::Compound* m_compound;
        };
    }
}
#endif	/* COMPOUNDRENDERABLE_H */

