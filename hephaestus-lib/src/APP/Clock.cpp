/* 
 * File:   Clock.cpp
 * Author: chris
 * 
 * Created on March 23, 2014, 11:59 PM
 */

#include "Clock.h"
#include <cstdlib>
#include "../UTIL/hash.h"
#include "../LOG/Core.h"

#define NAME "Clock"

namespace APP {

    Clock::Clock()
    : m_freeTimers(Clock_CONST::NO_TIMERS) {
        gettimeofday(&m_startup, NULL);
        for (int i = 0; i < Clock_CONST::NO_TIMERS; i++)
            m_freeTimers.push(i);
    }

    Clock::~Clock() {
    }

    Clock& Clock::getInstance() {
        static Clock clock;
        return clock;
    }

    bool Clock::startTimer(const char* name) {
        unsigned int hash = UTIL::getHash(name);
        // check if timer present
        std::map<unsigned int, unsigned int>::const_iterator i = m_indexMap.find(hash);
        if (i == m_indexMap.end()) { // not found
            unsigned int index = m_freeTimers.top();
            m_freeTimers.pop();
            strncpy(m_timers[index].name, name, 32);
            m_timers[index].starttime = getTime();
            m_indexMap.insert(std::pair<unsigned int, unsigned int>(hash, index));
        } else { // found
            L(warning) << "Restarting timer: " << name;
            unsigned int index = (*i).second;
            m_timers[index].starttime = getTime();
        }
        return true;
    }

    unsigned long int Clock::stopTimer(const char* name) {
        unsigned int hash = UTIL::getHash(name);
        // check if timer present
        std::map<unsigned int, unsigned int>::const_iterator i = m_indexMap.find(hash);
        if (i == m_indexMap.end()) { // not found
            L(error) << "Unknown timer: " << name;
            return -1;
        } else { // found
            unsigned int index = (*i).second;
            m_freeTimers.push(index);
            m_indexMap.erase(index);
            return getTime() - m_timers[index].starttime;
        }
        
    }

    unsigned long int Clock::getTime() const {
        timeval now;
        gettimeofday(&now, NULL);

        unsigned long int msec;
        msec = (now.tv_sec - m_startup.tv_sec)*1000;
        msec += (now.tv_usec - m_startup.tv_usec) / 1000;
        return msec;
    }

}
