/* 
 * File:   FileServer.cpp
 * Author: chris
 * 
 * Created on June 9, 2013, 7:24 PM
 */

#include "FileServer.h"
#include "Loader.h"
#include <iostream>
#include <assert.h>
#include "parseMetaData.h"
#include "Resource.h"
#include "../ERR/ERR.h"
#include "../UTIL/hash.h"
#include "../LOG/Core.h"
#include "EventListener.h"

#define DEBUG
#define NAME "FileServer"

namespace FSVR {

    FileServer::FileServer()
    : m_processingQueue(false)
    , m_bundleIndex(16, 16) {
    }

    FileServer::~FileServer() {
        while (m_requests.size() > 0) {
            std::cout << "Deleting request..." << std::endl;
            std::cout.flush();
            Request* request = m_requests.front();
            m_requests.pop();
            delete request;
        }
        for (std::vector<ResourceMetaData*>::const_iterator iter = m_resourceMetaData.begin(),
                end = m_resourceMetaData.end(); iter != end; ++iter)
            delete (*iter);
        }

    void FileServer::attachBundle(BNDL::Bundle& bundle) {
        // load metadata
        unsigned char* pData;
        int nBytes = bundle.read(METADATA_POSITION, &pData);
        std::list<ResourceMetaData*> metadata = parseMetaData(bundle.getMetaData(), bundle.getID());
        delete [] pData;

        for (std::list<ResourceMetaData*>::const_iterator iter = metadata.begin(),
                end = metadata.end(); iter != end; ++iter) {
            m_resourceIndex.add(UTIL::hash((*iter)->getResourceID()), m_resourceMetaData.size());
            m_resourceMetaData.push_back((*iter));
        }

        m_bundleIndex.add(UTIL::hash(bundle.getID()), m_resourceBundles.size());
        m_resourceBundles.push_back(&bundle);
    }

    BNDL::Bundle* FileServer::getBundlePtr(const BNDL::tBID& bID) {
        BNDL::Bundle* b = 0;
        int index = m_bundleIndex.first(UTIL::hash(bID));
        while ((index != MEM::HashIndex_CONST::INVALID_INDEX) && (m_resourceBundles[index]->getID() != bID))
            index = m_bundleIndex.next(index);
        if (index != MEM::HashIndex_CONST::INVALID_INDEX)
            b = m_resourceBundles[index];
        return b;
    }

    const ResourceMetaData* FileServer::getMetaData(const FSVR::tRID& id) const {
        // retrieve meta data for the resource        
        int index = m_resourceIndex.first(UTIL::hash(id));

        while ((index != MEM::HashIndex_CONST::INVALID_INDEX) && (m_resourceMetaData[index]->getResourceID() != id))
            index = m_resourceIndex.next(index);

        if (index != MEM::HashIndex_CONST::INVALID_INDEX)
            return m_resourceMetaData[index];
        else
            return 0;
    }

    void FileServer::backgroundLoad(Resource& resource, Loader* loader) {
        // retrieve meta data for the resource        
        int index = m_resourceIndex.first(UTIL::hash(resource.getID()));
        while ((index != MEM::HashIndex_CONST::INVALID_INDEX) && (m_resourceMetaData[index]->getResourceID() != resource.getID())) {
            index = m_resourceIndex.next(index);
        }
        if (index != MEM::HashIndex_CONST::INVALID_INDEX) {
            // create a new request and enqueue it
            const ResourceMetaData& metaData = *m_resourceMetaData[index];
            Request* request = new Request(resource, loader, metaData);
            // lock queue
            m_mtxQueue.lock();
            m_requests.push(request);
            // unlock queue
            m_mtxQueue.unlock();
        } else {
            //raise exception
            L(error) << "Could not find meta data for resource " << resource.getID();
            THROWS("Unable to load resource " + resource.getID());
        }
    }

    void FileServer::foregroundLoad(Resource& resource, Loader* loader) {
        // retrieve meta data for the resource        
        int index = m_resourceIndex.first(UTIL::hash(resource.getID()));
        while ((index != MEM::HashIndex_CONST::INVALID_INDEX) && (m_resourceMetaData[index]->getResourceID() != resource.getID()))
            index = m_resourceIndex.next(index);

        if (index != MEM::HashIndex_CONST::INVALID_INDEX) {
            const ResourceMetaData& metaData = *m_resourceMetaData[index];

            // determine bunde and acquire pointer
            BNDL::Bundle* pBundle = 0;
            pBundle = getBundlePtr(metaData.getBundleID());
            if (pBundle == 0) {
                L(error) << "Could not find bundle with bundleId " << metaData.getBundleID();
                THROWS("Unable to find bundle " + metaData.getBundleID());
            }

            // load raw data
            int nBytes;
            unsigned char* pData;
            nBytes = pBundle->read(metaData.getLocation(), &pData);

            // fill loader
            loader->setRawData(pData, nBytes);

            // Instantiation: Data: Loader ==> Resource
            resource.lock();
            loader->onLoadComplete(resource, metaData);
            resource.unlock();

            // notify
            if (resource.getEventListener())
                resource.getEventListener()->onLoadComplete(resource);


            // delete the loader and the raw data
            if (resource.isLoaderToBeDeleted()) {
                delete loader;
            }
        } else {
            //raise exception
            L(error) << "Could not find meta data for resource " << resource.getID();
            THROWS("Unable to load resource " + resource.getID());
        }
    }

    void FileServer::foregroundLoadRaw(FSVR::tRID id, unsigned char ** data, int * bytes) {
        // retrieve meta data for the resource        
        int index = m_resourceIndex.first(UTIL::hash(id));
        while ((index != MEM::HashIndex_CONST::INVALID_INDEX) && (m_resourceMetaData[index]->getResourceID() != id)) {
            index = m_resourceIndex.next(index);
        }
        if (index != MEM::HashIndex_CONST::INVALID_INDEX) {
            BNDL::Bundle* bundle = 0;
            bundle = getBundlePtr(m_resourceMetaData[index]->getBundleID());
            if (bundle == 0) {
                L(error) << "Could not find bundle with bundleId " << m_resourceMetaData[index]->getBundleID();
                THROWS("Unable to find bundle " + m_resourceMetaData[index]->getBundleID());
            }

            *bytes = bundle->read(m_resourceMetaData[index]->getLocation(), data);
        } else {
            //raise exception
            L(error) << "Could not find meta data for resource " << id;
            THROWS("Unable to load resource " + id);
        }

    }

    void FileServer::waitForLoadingFinished() {
        while (!isLoadingFinished())
            boost::this_thread::sleep(boost::posix_time::milliseconds(500));
        L(normal) << "Loading finished.";
    }

    bool FileServer::isLoadingFinished() {
        bool queueEmpty = false;
        m_mtxQueue.lock();
        if (m_requests.size() == 0)
            queueEmpty = true;
        m_mtxQueue.unlock();

        return (queueEmpty && (!m_processingQueue));
    }

    void FileServer::processQueue() {
        m_mtxQueue.lock();
        // move the current queue
        std::queue<Request*> requests = m_requests;
        m_requests = std::queue<Request*>();
        m_processingQueue = true;
        m_mtxQueue.unlock();

        while (requests.size() > 0) {
            Request* request = requests.front();
            requests.pop();

            // process request
            const ResourceMetaData& meta = request->getMetaData();
            const BNDL::tBID bundleID = meta.getBundleID();
            int nBytes;
            unsigned char* pData;

            BNDL::Bundle* pBundle = 0;
            pBundle = getBundlePtr(bundleID);
            if (pBundle == 0) {
                L(error) << "Could not find bundle with bundleId " << bundleID;
                THROWS("Unable to find bundle " + bundleID);
            }
            nBytes = pBundle->read(meta.getLocation(), &pData);

            // fill loader
            Loader* loader = request->getLoader();
            if (!loader) {
                L(error) << "Factory failed to produce a Loader.";
                THROWS("Factory failed to produce a Loader.");
            }
            loader->setRawData(pData, nBytes);

            request->getResource().lock();
            // data: Loader ==> Resource
            loader->onLoadComplete(request->getResource(), meta);
            request->getResource().unlock();

            if (request->getResource().getEventListener())
                request->getResource().getEventListener()->onLoadComplete(request->getResource());

            delete request;
        }
        m_processingQueue = false;
    }

    void FileServer::listMetaData() {
        for (std::vector<ResourceMetaData*>::const_iterator i = m_resourceMetaData.begin(),
                e = m_resourceMetaData.end();
                i != e;
                ++i) {
            L(normal) << "Resource ID: " << (*i)->getResourceID();
            L(normal) << "Bundle ID: " << (*i)->getBundleID();
            L(normal) << "Location: " << (*i)->getLocation();
            L(normal) << "Type: " << (*i)->getType() << "\n";
        }
    }
}