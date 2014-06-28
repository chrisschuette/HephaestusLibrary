/* 
 * File:   Request.h
 * Author: chris
 *
 * Created on June 10, 2013, 1:37 AM
 */

#ifndef REQUEST_H
#define	REQUEST_H

#include "ResourceMetaData.h"

namespace FSVR {
    class Resource;
    class Loader;

    class Request {
    public:
        Request(Resource& resource, Loader* loader, const ResourceMetaData& metaData);
        const ResourceMetaData& getMetaData() const { return m_metaData; }
        Loader* getLoader() const { return m_loader; }
        void setLoader(Loader* loader) { m_loader = loader; }
        Resource& getResource() { return m_resource; }
        virtual ~Request();
    private:
        Resource& m_resource;
        Loader* m_loader;
        const ResourceMetaData& m_metaData;
    };
}
#endif	/* REQUEST_H */

