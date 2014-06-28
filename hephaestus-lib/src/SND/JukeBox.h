/* 
 * File:   JukeBox.h
 * Author: chris
 *
 * Created on June 3, 2014, 11:05 PM
 */

#ifndef JUKEBOX_H
#define	JUKEBOX_H

#include "../FSVR/RID.h"
#include "../SYS/Handle.h"
#include "SoundInstance.h"
#include "EventListener.h"
#include "../FSVR/EventListener.h"
#include <list>

namespace SND {
    class SoundManager;

    class JukeBox : public SND::EventListener, public FSVR::EventListener {
    public:
        JukeBox(SoundManager& soundManager);
        virtual ~JukeBox();

        void addToPlaylist(FSVR::tRID song) {
            m_playlist.push_back(song);
        }
        void play();
        virtual void onLoadComplete(FSVR::Resource& resource);
        virtual void onPlaybackStart(SND::SoundInstance& instance);
        virtual void onPlaybackEnd(SND::SoundInstance& instance);

    private:
        SoundManager& m_soundManager;
        SYS::Handle<SoundInstance> m_currentSoundInstance;
        std::list<FSVR::tRID> m_playlist;
        std::list<FSVR::tRID>::const_iterator m_currentlyPlaying;
    };
}

#endif	/* JUKEBOX_H */

