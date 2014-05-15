/* 
 * File:   ResourceManager.cpp
 * Author: chris
 * 
 * Created on June 9, 2013, 7:54 PM
 */

#include "ResourceManager.h"

ResourceManager::ResourceManager()
:// m_textureLdrFty(REND::TextureLoaderFactory())
//, m_textureMgr(DMGD::ResourceManager<REND::Texture>(m_textureLdrFty, m_fileServer))
//, m_soundsMgr(DMGD::ResourceManager<SND::Sound>(m_soundLdrFty, m_fileServer))
m_fileServerLoop(m_fileServer) {
}

ResourceManager::~ResourceManager() {
    if (isFileServerRunning())
        stopFileServer();
}

void ResourceManager::attachBundle(BNDL::Bundle& bundle) {
    m_fileServer.attachBundle(bundle);
    m_fileServer.listMetaData();
}
/*
void ResourceManager::deleteTexture(FSVR::tRID id) {
    m_textureMgr.deleteResource(id);
}

void ResourceManager::loadTexture(FSVR::tRID id, FSVR::Resource::INSTANTIATION instantiation) {
    // pass the load call to the texture manager
    m_textureMgr.loadResource(id, instantiation);
}

void ResourceManager::loadSound(FSVR::tRID id, FSVR::Resource::INSTANTIATION instantiation) {
    // pass the load call to the sounds manager
    m_soundsMgr.loadResource(id, instantiation);
}

DMGD::Resource<REND::Texture>* ResourceManager::getTexture(FSVR::tRID id) {
    return m_textureMgr.getResource(id);
}

SYS::Handle<REND::Texture> ResourceManager::getTextureHandle(FSVR::tRID id) {
    return m_textureMgr.getResourceHandle(id);
}

void ResourceManager::showTextureInfo() {
    m_textureMgr.showResourceInfo();
}
*/
void ResourceManager::startFileServer() {
    m_fileServerThread = boost::thread(boost::ref(m_fileServerLoop));
}

void ResourceManager::stopFileServer() {
    m_fileServerLoop.setRunning(false);
    m_fileServerThread.join();
}

bool ResourceManager::isFileServerRunning() {
    return (m_fileServerLoop.isRunning() && !m_fileServerThread.timed_join(boost::posix_time::seconds(0)));
}

