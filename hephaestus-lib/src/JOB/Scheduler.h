/* 
 * File:   Scheduler.h
 * Author: chris
 *
 * Created on June 12, 2014, 9:42 AM
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include <list>

namespace JOB {
    struct Job;
    class Scheduler {
    public:
        Scheduler();
        virtual ~Scheduler();
        
        void update(unsigned long int currentTime);
        void scheduleJob(Job* job);
        void cancelJob(Job* job);
    private:
        std::list<Job*> m_jobList;
    };
}
#endif	/* SCHEDULER_H */

