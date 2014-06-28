/* 
 * File:   XMLMetaData.h
 * Author: chris
 *
 * Created on June 1, 2014, 11:52 AM
 */

#ifndef XMLMETADATA_H
#define	XMLMETADATA_H

#include "MetaData.h"
#include <rapidxml.hpp>

namespace BNDL {

    class XMLMetaData: public MetaData {
    public:
        XMLMetaData(unsigned char * pData, int nBytes);
        virtual ~XMLMetaData();
        
        const rapidxml::xml_document<>& getXMLDocument() const { return m_doc; }
    private:
        rapidxml::xml_document<> m_doc;
        char * m_xml;
    };
}
#endif	/* XMLMETADATA_H */

