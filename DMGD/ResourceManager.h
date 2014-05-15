/* 
 * File:   ResourceManager.h
 * Author: chris
 *
 * Created on June 9, 2013, 7:55 PM
 */

#ifndef DMGD_RESOURCEMANAGER_H
#define	DMGD_RESOURCEMANAGER_H

#include "../FSVR/RID.h"
#include "Resource.h"
#include "LoaderFactory.h"
#include "../FSVR/FileServer.h"
#include "../DMGD/Loader.h"
#include "../SYS/Reference.h"
#include "../SYS/Handle.h"
#include "../MEM/Pool.h"
#include "../LOG/Source.h"

#include <map>
#include <iostream>

namespace DMGD {

    template <class T>
    class LoaderFactory;

    namespace ResourceManager_CONST {
        const int MAX_RESOURCE_REFERENCES = 200;
    }

    template <class T>
    class ResourceManager : public LOG::Source {
    public:

        ResourceManager(LoaderFactory<T>& loaderFactory, FSVR::FileServer& fileServer)
        : LOG::Source("ResourceManager")
        , m_referencePool(ResourceManager_CONST::MAX_RESOURCE_REFERENCES)
        , m_loaderFactory(loaderFactory)
        , m_fileServer(fileServer) {
        }

        Resource<T>* loadResource(FSVR::tRID id, FSVR::Resource::INSTANTIATION instantiation) {
            // create new resource
            Resource<T>* pResource = new Resource<T > (id, m_referencePool);
            pResource->setInstantiation(instantiation);

            // set state to LOADING
            pResource->setState(FSVR::Resource::LOADING);

            // create an appropriate loader
            Loader<T>* pLoader = m_loaderFactory.createLoader();

            // order the file from the fileserver
            m_fileServer.backgroundLoad(*pResource, pLoader);

            // insert into map
            m_resourcePtrs.insert(std::pair<FSVR::tRID, Resource<T>*>(id, pResource));

            return pResource;
        }

        Resource<T>* getResource(FSVR::tRID id) {
            typename std::map<FSVR::tRID, Resource<T>*>::iterator i = m_resourcePtrs.find(id);
            if (i == m_resourcePtrs.end()) {
                // raise exception
                L(error) << "Unknown resource " << id;
                return 0;
            }
            Resource<T>* resource = (*i).second;

            if (resource->getState() == FSVR::Resource::ACTIVE) {
                L(normal) << "Resource " << id << " is active.";
                return resource;
            }
            else {
                L(normal) << "JIT instantiation of resource " << id;
                // resource must be instantiated
                FSVR::Loader* loader = resource->getLoader();
                const FSVR::ResourceMetaData* metadata = m_fileServer.getMetaData(id);
                if (loader && metadata) {

                    loader->instantiate(*resource, *metadata);
                    // success?
                    if (resource->getState() == FSVR::Resource::ACTIVE) {
                        // strip the loader from the resource to
                        // free the memory of the raw resource data.
                        resource->setLoader(0);
                        delete loader;
                        return resource;
                    } else {
                        L(error) << "Instantiation failed.";
                        return 0;
                    }
                } else {
                    // raise exception
                    L(error) << "No loader or no metadata available. Can't instantiate resource "
                            << resource->getID();
                    return 0;
                }
            }
        }

        SYS::Handle<T> getResourceHandle(FSVR::tRID id) {
            typename std::map<FSVR::tRID, Resource<T>*>::iterator i = m_resourcePtrs.find(id);
            if (i == m_resourcePtrs.end()) {
                // raise exception
                L(error) << "Unknown resource " << id;
                //create an empty handle
                return SYS::Handle<T > (0, m_referencePool);
            }
            Resource<T>* resource = (*i).second;

            if (resource->getState() == FSVR::Resource::ACTIVE)
                return resource->getHandle();
            else {
                // resource must be instantiated
                FSVR::Loader* loader = resource->getLoader();
                const FSVR::ResourceMetaData* metadata = m_fileServer.getMetaData(id);

                if (loader && metadata) {
                    loader->instantiate(*resource, *metadata);
                    // success?
                    if (resource->getState() == FSVR::Resource::ACTIVE) {
                        // strip the loader from the resource to
                        // free the memory of the raw resource data.
                        resource->setLoader(0);
                        delete loader;
                        return resource->getHandle();
                    } else {
                        L(error) << "Instantiation failed.";
                        //create an empty handle
                        return SYS::Handle<T > (0, m_referencePool);
                    }
                } else {
                    // raise exception
                    L(error) << "No loader or no metadata available. Can't instantiate resource."
                            << resource->getID();
                    //create an empty handle
                    return SYS::Handle<T > (0, m_referencePool);
                }
            }
        }

        void deleteResource(FSVR::tRID id) {
            typename std::map<FSVR::tRID, Resource<T>*>::iterator i = m_resourcePtrs.find(id);
            if (i == m_resourcePtrs.end()) {
                // raise exception
                L(error) << "Unknown resource " << id;
            }
            Resource<T>* resource = (*i).second;
            if (resource->getState() == FSVR::Resource::LOADING) {
                L(error) << "Can't delete loading resource " << id;
            } else {
                delete resource;
                m_resourcePtrs.erase(i);
            }
        }

        void purgeResources() {
            // delete all resources in the map
            for (typename std::map<FSVR::tRID, Resource<T>*>::iterator i = m_resourcePtrs.begin(),
                    end = m_resourcePtrs.end(); i != end; ++i) {
                Resource<T>* pResource = (*i).second;
                if (pResource)
                    delete pResource;
            }
            m_resourcePtrs.clear();
        }

        virtual ~ResourceManager() {
            purgeResources();
        }

        void showResourceInfo() {
            L(normal) << "Num. of resources: " << m_resourcePtrs.size();
            for (typename std::map<FSVR::tRID, Resource<T>*>::iterator i = m_resourcePtrs.begin(),
                    end = m_resourcePtrs.end(); i != end; ++i) {
                Resource<T>* pResource = (*i).second;
                L(normal) << "ID: " << pResource->getID();
                std::string state;
                switch (pResource->getState()) {
                    case FSVR::Resource::INACTIVE:
                        state = "inactive";
                        break;
                    case FSVR::Resource::LOADING:
                        state = "loading";
                        break;
                    case FSVR::Resource::ACTIVE:
                        state = "active";
                        break;
                    case FSVR::Resource::RAW:
                        state = "raw";
                        break;
                    case FSVR::Resource::FAILED:
                        state = "failed";
                        break;
                    default:
                        state = "unknown";
                }
                L(normal) << "STATE: " << state << " REF. COUNT: " << pResource->getReferenceCount();
            }
        }
    protected:
        LoaderFactory<T>& m_loaderFactory;
        FSVR::FileServer& m_fileServer;

        std::map<FSVR::tRID, Resource<T>*> m_resourcePtrs;
        MEM::Pool< SYS::Reference<T> > m_referencePool;
    };
}

#endif	/* DMGD_RESOURCEMANAGER_H */

