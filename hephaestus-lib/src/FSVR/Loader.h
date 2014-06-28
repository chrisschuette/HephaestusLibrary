/* 
 * File:   Loader.h
 * Author: chris
 *
 * Created on June 9, 2013, 8:35 PM
 */

#ifndef FSVR_LOADER_H
#define	FSVR_LOADER_H

#include <string>

namespace FSVR {
    class Resource;
    class ResourceMetaData;
    
    class Loader {
    public:
        Loader();
        virtual ~Loader();

        virtual void onLoadComplete(Resource& resource, const ResourceMetaData& metadata);
        virtual void instantiate(Resource& resource, const ResourceMetaData& metadata);

        unsigned char * getRawData() {
            return m_rawData;
        }

        const unsigned char * getRawData() const {
            return m_rawData;
        }

        int getRawDataSize() {
            return m_rawDataSize;
        }

        void setRawData(unsigned char * pRawData, int rawDataSize) {
            m_rawData = pRawData;
            m_rawDataSize = rawDataSize;
        }
        
        void discardRawData() {
            if(m_rawData) {
                delete [] m_rawData;
                m_rawData = 0;
            }
            m_rawDataSize = 0;
        }
    private:
        unsigned char * m_rawData;
        int m_rawDataSize;
    };
}
#endif	/* FSVR_LOADER_H */

