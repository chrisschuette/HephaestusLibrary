/* 
 * File:   MeshLoaderFactory.cpp
 * Author: chris
 * 
 * Created on May 30, 2014, 5:59 PM
 */

#include "MeshLoaderFactory.h"
#include "SVGMeshLoader.h"

namespace REND {
    namespace SHAPES {

        MeshLoaderFactory::MeshLoaderFactory(ShaderManager& shaderManager) : DMGD::LoaderFactory<REND::SHAPES::Mesh>(), m_shaderManager(shaderManager) {
        }

        MeshLoaderFactory::~MeshLoaderFactory() {
        }
        
        DMGD::Loader<REND::SHAPES::Mesh>* MeshLoaderFactory::createLoader() {
            return new SVGMeshLoader(m_shaderManager);
        }
    }
}
