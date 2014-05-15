/* 
 * File:   Clock.h
 * Author: chris
 *
 * Created on March 23, 2014, 11:59 PM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#include <sys/time.h>
#include <map>
#include "../MEM/Stack.h"
#include "../LOG/Source.h"

#define START_TIMER(x) APP::Clock::getInstance().startTimer(x)
#define STOP_TIMER(x) APP::Clock::getInstance().stopTimer(x)

namespace APP {
    namespace Clock_CONST {
        const static int NO_TIMERS = 32;
    }
    class Clock: public LOG::Source {
    public:
        struct TimerEntry {
            char name[32];
            unsigned long int starttime;
        };
    public:
        static Clock& getInstance();
        unsigned long int getTime() const;
        
        // timers
        bool startTimer(const char* name);
        unsigned long int stopTimer(const char* name);
    private:
        Clock();
        virtual ~Clock();
        timeval m_startup;
        
        // timers
        TimerEntry m_timers[Clock_CONST::NO_TIMERS];
        MEM::Stack<unsigned int> m_freeTimers;
        std::map<unsigned int, unsigned int> m_indexMap;
    };
}
#endif	/* CLOCK_H */

