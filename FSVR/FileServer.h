/* 
 * File:   FileServer.h
 * Author: chris
 *
 * Created on June 9, 2013, 7:24 PM
 */

#ifndef FILESERVER_H
#define	FILESERVER_H

#include "RID.h"
#include "../BNDL/BID.h"
#include "../BNDL/RID.h"
#include "../BNDL/Bundle.h"
#include "ResourceMetaData.h"
#include "Request.h"
#include "../LOG/Source.h"

#include <map>
#include <vector>
#include <queue>
#include <boost/thread/thread.hpp>

#include "../MEM/HashIndex.h"

namespace FSVR {
    class Loader;
    class Resource;

    class FileServer: public LOG::Source {
    public:

        class LoadLoop: public LOG::Source {
        public:

            LoadLoop(FileServer& fileServer)
            : LOG::Source("LoadLoop")
            , m_fileServer(fileServer)
            , m_run(false) {

            }

            void setRunning(bool run) {
                m_run = run;
            }
            
            bool isRunning() {
                return m_run;
            }

            void operator()() {
                m_run = true;
                while (m_run) {
                    //L(normal) << "Processing queue.";
                    m_fileServer.processQueue();
                    boost::this_thread::sleep(boost::posix_time::milliseconds(500));
                }
            }
        private:
            FileServer& m_fileServer;
            bool m_run;
        };
    public:
        FileServer();
        virtual ~FileServer();

        void attachBundle(BNDL::Bundle& bundle);
        BNDL::Bundle* getBundlePtr(const BNDL::tBID& bID);
        
        const ResourceMetaData* getMetaData(const FSVR::tRID& id) const;
        
        void backgroundLoad(Resource& resource, Loader* loader);
        void foregroundLoad(Resource& resource, Loader* loader);
        
        void foregroundLoadRaw(FSVR::tRID id, unsigned char ** data, int * bytes);
        void processQueue();
        
        bool isLoadingFinished();
        void waitForLoadingFinished();

        //debug
        void listMetaData();
    private:
        // m_bundleIndex + m_resourceBundles should be faster
        //std::map<BNDL::tBID, BNDL::Bundle*> m_bundles;
        
        MEM::HashIndex m_bundleIndex;
        std::vector<BNDL::Bundle*> m_resourceBundles;
        
        //std::map<tRID, ResourceMetaData> m_metaData;
        
        MEM::HashIndex m_resourceIndex;
        std::vector<ResourceMetaData> m_resourceMetaData;
        
        std::queue<Request*> m_requests;
        bool m_processingQueue;

        // threading
        boost::mutex m_mtxQueue;
    };
}
#endif	/* FILESERVER_H */

