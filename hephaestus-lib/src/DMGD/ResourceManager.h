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
#include "../LOG/Core.h"
#include "../FSVR/EventListener.h"
#include "../UTIL/string.h"

#include <map>
#include <iostream>

namespace DMGD {

    template <class T>
    class LoaderFactory;

    namespace ResourceManager_CONST {
        const int MAX_RESOURCE_REFERENCES = 200;
    }

    template <class T>
    class ResourceManager {
    public:

        ResourceManager(LoaderFactory<T>& loaderFactory, FSVR::FileServer& fileServer)
        : m_referencePool(ResourceManager_CONST::MAX_RESOURCE_REFERENCES)
        , m_loaderFactory(loaderFactory)
        , m_fileServer(fileServer) {
        }

        std::string generateNewResourceID() {
            std::string RID;
            bool found = false;
            while (!found) {
                RID = "R_";
                RID += UTIL::getRandomString(10);
                typename std::map<FSVR::tRID, Resource<T>*>::iterator i = m_resourcePtrs.find(RID);
                if (i == m_resourcePtrs.end())
                    found = true;
            }
            return RID;
        }

        Resource<T>* addResource(FSVR::tRID id, T* data) {
            Resource<T>* pResource = new Resource<T > (id, m_referencePool);
            pResource->setInstantiation(FSVR::Resource::IMMEDIATELY);
            pResource->setState(FSVR::Resource::ACTIVE);
            pResource->setInstance(data);
            if(data == 0) {
                L_SENDER(warning, "ResourceManager") << "No resource provided. Not adding.";
                return 0;
            }
            m_resourcePtrs.insert(std::pair<FSVR::tRID, Resource<T>*>(id, pResource));

            //if(!result.second)
            //    return 0; // insert failed (id already used)

            return pResource;
        }

        Resource<T>* loadResource(FSVR::tRID id, FSVR::Resource::INSTANTIATION instantiation, FSVR::EventListener* eventListener = 0) {
            // check if already loaded
            typename std::map<FSVR::tRID, Resource<T>*>::iterator i = m_resourcePtrs.find(id);
            if (i != m_resourcePtrs.end()) {
                if (eventListener)
                    eventListener->onLoadComplete(*((*i).second));
                return (*i).second;
            }

            // create new resource
            Resource<T>* pResource = new Resource<T > (id, m_referencePool);
            pResource->setInstantiation(instantiation);
            pResource->setEventListener(eventListener);

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
                //L(error) << "Unknown resource " << id;
                return 0;
            }
            Resource<T>* resource = (*i).second;

            if (resource->getState() == FSVR::Resource::ACTIVE) {
                //L(normal) << "Resource " << id << " is active.";
                return resource;
            } else {
                //L(normal) << "JIT instantiation of resource " << id;
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
                        //L(error) << "Instantiation failed.";
                        return 0;
                    }
                } else {
                    // raise exception
                    //L(error) << "No loader or no metadata available. Can't instantiate resource "
                    //                            << resource->getID();
                    return 0;
                }
            }
        }

        SYS::Handle<T> getResourceHandle(FSVR::tRID id) {
            typename std::map<FSVR::tRID, Resource<T>*>::iterator i = m_resourcePtrs.find(id);
            if (i == m_resourcePtrs.end()) {
                // raise exception
                //L(error) << "Unknown resource " << id;
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
                        //L(error) << "Instantiation failed.";
                        //create an empty handle
                        return SYS::Handle<T > (0, m_referencePool);
                    }
                } else {
                    // raise exception
                    //L(error) << "No loader or no metadata available. Can't instantiate resource."
                    //        << resource->getID();
                    //create an empty handle
                    return SYS::Handle<T > (0, m_referencePool);
                }
            }
        }

        void deleteResource(FSVR::tRID id) {
            typename std::map<FSVR::tRID, Resource<T>*>::iterator i = m_resourcePtrs.find(id);
            if (i == m_resourcePtrs.end()) {
                // raise exception
                //L(error) << "Unknown resource " << id;
            }
            Resource<T>* resource = (*i).second;
            if (resource->getState() == FSVR::Resource::LOADING) {
                //L(error) << "Can't delete loading resource " << id;
            } else {
                delete resource;
                m_resourcePtrs.erase(i);
            }
        }

        void purgeUnreferencedResources() {
            int count = 0;
            typename std::map<FSVR::tRID, Resource<T>*>::iterator i = m_resourcePtrs.begin();
            while (i != m_resourcePtrs.end()) {
                Resource<T>* pResource = (*i).second;
                if (pResource && (pResource->getReferenceCount() == 0)) {
                    count++;
                    m_resourcePtrs.erase(i++);
                    delete pResource;
                } else
                    ++i;
            }
            if(count)
                L_SENDER(normal, "ResourceManager") << "Cleaned " << count << " resources.";
        }

        void purgeResources() {
            // delete all resources in the map
            for (typename std::map<FSVR::tRID, Resource<T>*>::iterator i = m_resourcePtrs.begin(),
                    end = m_resourcePtrs.end(); i != end; ++i) {
                //L_SENDER(normal, "ResourceManager") << "Deleting " << (*i).first;
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
            L_SENDER(normal, "ResourceManager") << "Num. of resources: " << m_resourcePtrs.size();
            for (typename std::map<FSVR::tRID, Resource<T>*>::iterator i = m_resourcePtrs.begin(),
                    end = m_resourcePtrs.end(); i != end; ++i) {
                Resource<T>* pResource = (*i).second;
                L_SENDER(normal, "ResourceManager") << "ID: " << pResource->getID();
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
                L_SENDER(normal, "ResourceManager") << "STATE: " << state << " REF. COUNT: " << pResource->getReferenceCount();
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

