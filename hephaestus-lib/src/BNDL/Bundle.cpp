/* 
 * File:   Bundle.cpp
 * Author: chris
 * 
 * Created on June 10, 2013, 12:48 AM
 */

#include "Bundle.h"
#include "MetaData.h"
#include "../ERR/ERR.h"
#include <iostream>

namespace BNDL {

    Bundle::Bundle(tBID id) : m_ID(id), m_bundleMetaData(0) {
    }

    Bundle::~Bundle() {
        if (m_bundleMetaData)
            delete m_bundleMetaData;
    }

    MetaData& Bundle::getMetaData() {
        if(!m_bundleMetaData)
            THROWS("No meta data available.");
        return *m_bundleMetaData;
    }

}
