/* 
 * File:   SVGMeshLoader.h
 * Author: chris
 *
 * Created on May 30, 2014, 6:06 PM
 */

#ifndef SVGMESHLOADER_H
#define	SVGMESHLOADER_H

#include "Mesh.h"
#include "../../DMGD/Loader.h"
#include "../../GEOMETRY/Compound.h"

#include <list>

namespace GL {
    class GLVertexBuffer;
}

namespace REND {
    class ShaderManager;
    namespace SHAPES {

        class SVGMeshLoader : public DMGD::Loader<REND::SHAPES::Mesh> {
        public:
            SVGMeshLoader(REND::ShaderManager& shaderManager);
            virtual ~SVGMeshLoader();

            virtual void onLoadComplete(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata);
            virtual void instantiate(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata);
            static GL::GLVertexBuffer* createBuffer(const GEOMETRY::Compound& compound );
            
        private:
            std::list<GEOMETRY::Compound*> m_compoundList;
            REND::ShaderManager& m_shaderManager;
        };
    }
}
#endif	/* SVGMESHLOADER_H */

