/* 
 * File:   XMLResourceMetaData.cpp
 * Author: chris
 * 
 * Created on June 1, 2014, 12:12 PM
 */

#include "XMLResourceMetaData.h"

namespace FSVR {

    XMLResourceMetaData::XMLResourceMetaData(rapidxml::xml_node<>* resource_node) : ResourceMetaData(), m_resourceNode(resource_node) {
    }

    XMLResourceMetaData::~XMLResourceMetaData() {
    }

    const char* XMLResourceMetaData::getValue(const char* key) const {
        using namespace rapidxml;
        if(m_resourceNode) {
            xml_node<> * node = m_resourceNode->first_node(key);
            if(node)
                return node->value();
        }
        return 0;
    }
}
