/* 
 * File:   Request.cpp
 * Author: chris
 * 
 * Created on June 10, 2013, 1:37 AM
 */

#include "Request.h"
#include "Loader.h"
#include "Resource.h"
#include <iostream>

namespace FSVR {
Request::Request(Resource& resource, Loader* loader, const ResourceMetaData& metaData)
: m_resource(resource)
, m_loader(loader)
, m_metaData(metaData)
{
}

Request::~Request() {
    if(m_loader && m_resource.isLoaderToBeDeleted()) {
        delete m_loader;
    }
}
}