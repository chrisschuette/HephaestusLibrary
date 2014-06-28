/* 
 * File:   XMLMetaData.cpp
 * Author: chris
 * 
 * Created on June 1, 2014, 11:52 AM
 */

#include "XMLMetaData.h"
#include <string.h>

namespace BNDL {

    XMLMetaData::XMLMetaData(unsigned char * pData, int nBytes) : MetaData(), m_xml(0) {
        using namespace rapidxml;

        m_xml = new char[nBytes + 1];
        memcpy(m_xml, pData, nBytes);
        m_xml[nBytes] = 0;
        m_doc.parse < 0 > (m_xml); // 0 means default parse flags
    }

    XMLMetaData::~XMLMetaData() {
        if(m_xml)
            delete [] m_xml;
    }
}
