/* 
 * File:   JukeBox.cpp
 * Author: chris
 * 
 * Created on June 3, 2014, 11:05 PM
 */

#include "JukeBox.h"
#include "SoundManager.h"
#include "../LOG/Core.h"

#define NAME "JukeBox"

namespace SND {

    JukeBox::JukeBox(SoundManager& soundManager)
    : SND::EventListener()
    , FSVR::EventListener()
    , m_soundManager(soundManager)
    , m_currentSoundInstance(0, m_soundManager)
    , m_currentlyPlaying(m_playlist.end()) {

    }

    void JukeBox::play() {
        if (m_playlist.size() == 0)
            return;
        if (m_currentlyPlaying == m_playlist.end())
            m_currentlyPlaying = m_playlist.begin();

        FSVR::tRID song_name = *m_currentlyPlaying;

        m_soundManager.loadResource(song_name, FSVR::Resource::IMMEDIATELY, this);
    }

    void JukeBox::onLoadComplete(FSVR::Resource& resource) {
        FSVR::tRID song_name = *m_currentlyPlaying;
        m_currentSoundInstance = m_soundManager.getSoundInstance(song_name);
        m_currentSoundInstance->setEventListener(this);
        m_currentSoundInstance->play();
        m_soundManager.unloadUnusedResources();
    }
    
    void JukeBox::onPlaybackStart(SND::SoundInstance& instance) {
        L(normal) << "PLAYING: " << *m_currentlyPlaying;
    }

    void JukeBox::onPlaybackEnd(SND::SoundInstance& instance) {
        L(normal) << "PLAYING STOPPED: " << *m_currentlyPlaying;
        // advance playlist
        ++m_currentlyPlaying;

        if (m_currentlyPlaying == m_playlist.end())
            return;

        FSVR::tRID song_name = *m_currentlyPlaying;

        m_soundManager.loadResource(song_name, FSVR::Resource::IMMEDIATELY, this);
    }

    JukeBox::~JukeBox() {
    }
}
