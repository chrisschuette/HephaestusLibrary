/* 
 * File:   XMLResourceMetaData.h
 * Author: chris
 *
 * Created on June 1, 2014, 12:12 PM
 */

#ifndef XMLRESOURCEMETADATA_H
#define	XMLRESOURCEMETADATA_H

#include "ResourceMetaData.h"
#include <rapidxml.hpp>

namespace FSVR {

    class XMLResourceMetaData: public ResourceMetaData {
    public:
        XMLResourceMetaData(rapidxml::xml_node<>* resource_node);
        virtual ~XMLResourceMetaData();
        virtual const char* getValue(const char* key) const;
    private:
        rapidxml::xml_node<>* m_resourceNode;
    };
}
#endif	/* XMLRESOURCEMETADATA_H */

