/* 
 * File:   CompoundRenderable.cpp
 * Author: chris
 * 
 * Created on June 3, 2014, 10:02 AM
 */

#include "CompoundRenderable.h"
#include "../../GEOMETRY/Compound.h"

namespace REND {
    namespace SHAPES {

        CompoundRenderable::CompoundRenderable(GEOMETRY::Compound* compound, RenderBuffer* renderBuffer, ShaderProgramInstance shaderInstance)
        : REND::Renderable(renderBuffer, shaderInstance)
        , m_compound(compound) {
        }

        CompoundRenderable::~CompoundRenderable() {
            if(m_compound)
                delete m_compound;
        }
    }
}
