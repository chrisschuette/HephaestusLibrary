/* 
 * File:   ResourceManager.h
 * Author: chris
 *
 * Created on June 9, 2013, 7:54 PM
 */

#ifndef RESOURCEMANAGER_H
#define	RESOURCEMANAGER_H

#include "DMGD/ResourceManager.h"
#include "FSVR/RID.h"
#include "FSVR/FileServer.h"

#include "REND/TextureLoaderFactory.h"
#include "REND/Texture.h"

#include "SND/SoundLoaderFactory.h"
#include "SND/Sound.h"

namespace BNDL {
    class Bundle;
}

class ResourceManager {
public:
    ResourceManager();
    virtual ~ResourceManager();
    
    void attachBundle(BNDL::Bundle& bundle);
    /*
    // textures
    void loadTexture(FSVR::tRID id, FSVR::Resource::INSTANTIATION instantiation = FSVR::Resource::ONFIRSTUSE);
    void deleteTexture(FSVR::tRID id);
    DMGD::Resource<REND::Texture>& getTexture(FSVR::tRID id);
    SYS::Handle<REND::Texture> getTextureHandle(FSVR::tRID id);
    void showTextureInfo();
    
    // sounds
    void loadSound(FSVR::tRID id, FSVR::Resource::INSTANTIATION instantiation = FSVR::Resource::IMMEDIATELY);
    */
    FSVR::FileServer& getFileServer() { return m_fileServer; }
    
    void startFileServer();
    void stopFileServer();
    bool isFileServerRunning();
private:
    FSVR::FileServer m_fileServer;
    
    FSVR::FileServer::LoadLoop m_fileServerLoop;
    boost::thread m_fileServerThread;

};

#endif	/* RESOURCEMANAGER_H */

