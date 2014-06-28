#include "parseMetaData.h"
#include "../BNDL/XMLMetaData.h"
#include "XMLResourceMetaData.h"
#include <iostream>
#include <rapidxml.hpp>
#include <string.h>

namespace FSVR {

    std::list<ResourceMetaData*> parseMetaData(const BNDL::MetaData& meta_data, const BNDL::tBID& id) {
        
        std::list<ResourceMetaData*> metaDataList;

        using namespace rapidxml;
/*
        char * xml = new char[nBytes + 1];
        memcpy(xml, pData, nBytes);
        xml[nBytes] = 0;
        xml_document<> doc; // character type defaults to char
        doc.parse < 0 > (xml); // 0 means default parse flags
*/
        const xml_document<>& doc = static_cast<const BNDL::XMLMetaData&>(meta_data).getXMLDocument();
        
        // read bundle id
        xml_node<> *node = doc.first_node("bundleid");

        if (node->value() != id) {
            // raise exception
            std::cerr << "Bundle id in metadata file \"" << node->value() << "\" does not match "
                    << id << std::endl;
            return metaDataList;
        }

        node = doc.first_node("catalog");
        for (xml_node<> *resource = node->first_node();
                resource; resource = resource->next_sibling()) {
            XMLResourceMetaData* metaData = new XMLResourceMetaData(resource);
            metaData->setResourceID(resource->first_node("id")->value());
            metaData->setLocation(resource->first_node("location")->value());
            metaData->setBundleID(id);
            metaData->setType(resource->first_node("type")->value());
            metaDataList.push_back(metaData);
        }
        return metaDataList;
    }
}
