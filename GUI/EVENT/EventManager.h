/* 
 * File:   EventManager.h
 * Author: chris
 *
 * Created on February 2, 2014, 7:22 PM
 */

#ifndef GUI_EVENTMANAGER_H
#define	GUI_EVENTMANAGER_H

#include "../../INPUT/InputMap.h"
#include "../../LOG/Source.h"
#include "ID.h"
#include "../../GEOMETRY/Vec2.h"
#include <map>

namespace GUI {
    namespace EVENT {
        class EventListener;
        class EventManager: public INPUT::InputMap, public LOG::Source {
        public:
            EventManager();
            virtual ~EventManager();
            
            virtual ID getIDFromPosition(const GEOMETRY::Vec2<int>& position) = 0;
            void handleMouseInput(const INPUT::Input& input);
            void addEventListener(EventListener* eventListener);
            void reset();
            void showInfo();
        private:
            typedef std::map<ID, EventListener*> tEventListenerMap;
            tEventListenerMap m_listener;
            ID m_currentID;
            
            ID m_designated;
        };
    }
}
#endif	/* GUI_EVENTMANAGER_H */

