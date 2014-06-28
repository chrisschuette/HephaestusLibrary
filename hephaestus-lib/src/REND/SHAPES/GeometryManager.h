/* 
 * File:   GeometryManager.h
 * Author: chris
 *
 * Created on May 30, 2014, 5:54 PM
 */

#ifndef GEOMETRYMANAGER_H
#define	GEOMETRYMANAGER_H

#include "../../DMGD/ResourceManager.h"
#include "Mesh.h"

namespace REND {
    namespace SHAPES {

        class GeometryManager: public DMGD::ResourceManager<REND::SHAPES::Mesh> {
        public:
            GeometryManager(DMGD::LoaderFactory<REND::SHAPES::Mesh>& loaderFactory, FSVR::FileServer& fileServer);
            virtual ~GeometryManager();
        private:

        };
    }
}
#endif	/* GEOMETRYMANAGER_H */

