/* 
 * File:   MeshLoaderFactory.h
 * Author: chris
 *
 * Created on May 30, 2014, 5:59 PM
 */

#ifndef MESHLOADERFACTORY_H
#define	MESHLOADERFACTORY_H

#include "../../DMGD/LoaderFactory.h"
#include "Mesh.h"

namespace REND {
    class ShaderManager;
    namespace SHAPES {

        class MeshLoaderFactory: public DMGD::LoaderFactory<REND::SHAPES::Mesh> {
        public:
            MeshLoaderFactory(ShaderManager& shaderManager);
            virtual ~MeshLoaderFactory();
            
            DMGD::Loader<REND::SHAPES::Mesh>* createLoader();
        private:
            ShaderManager& m_shaderManager;
        };
    }
}
#endif	/* MESHLOADERFACTORY_H */

