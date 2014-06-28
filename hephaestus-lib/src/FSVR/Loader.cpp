/* 
 * File:   Loader.cpp
 * Author: chris
 * 
 * Created on June 9, 2013, 8:35 PM
 */

#include "Loader.h"
#include "Resource.h"
#include "../ERR/ERR.h"
#include "../LOG/Core.h"

#include <iostream>

#define NAME "Loader"

namespace FSVR {

    Loader::Loader()
    : m_rawData(0)
    , m_rawDataSize(0) {
    }

    Loader::~Loader() {
        if (m_rawData) {
            L(normal) << "Deleting raw data.";
            delete [] m_rawData;
        }
    }
    
    void Loader::instantiate(Resource& resource, const ResourceMetaData& metadata) {
        resource.setState(FSVR::Resource::ACTIVE);
    }

    void Loader::onLoadComplete(Resource& resource, const ResourceMetaData& metadata) {
        resource.setState(FSVR::Resource::RAW);
        if (resource.getInstantiation() == FSVR::Resource::IMMEDIATELY) {
            // instantiating resource
            L(normal) << "Instantiating..." ;
            instantiate(resource, metadata);
            // check
            if(resource.getState()!=Resource::ACTIVE) {
                L(error) << "Failed to instantiate resource " << resource.getID();
                THROWS("Resource instantiation failed.");
            }
        } else {
            // later 
            L(normal) << "Not instantiating. Attaching loader to resource.";
            resource.setLoader(this);
        }
    }

}