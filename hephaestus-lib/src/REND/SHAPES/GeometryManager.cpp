/* 
 * File:   GeometryManager.cpp
 * Author: chris
 * 
 * Created on May 30, 2014, 5:54 PM
 */

#include "GeometryManager.h"
#include "../../LOG/Core.h"

#define NAME "GeometryManager"

namespace REND {
    namespace SHAPES {

        GeometryManager::GeometryManager(DMGD::LoaderFactory<REND::SHAPES::Mesh>& loaderFactory, FSVR::FileServer& fileServer)
        : DMGD::ResourceManager<REND::SHAPES::Mesh>(loaderFactory, fileServer)
        {
            L(normal) << "GeometryManager up and running.";
        }

        GeometryManager::~GeometryManager() {
        }
    }
}
