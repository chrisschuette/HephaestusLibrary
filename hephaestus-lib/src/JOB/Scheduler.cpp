/* 
 * File:   Scheduler.cpp
 * Author: chris
 * 
 * Created on June 12, 2014, 9:42 AM
 */

#include "Scheduler.h"
#include "Job.h"

#include <algorithm>

namespace JOB {

    Scheduler::Scheduler() {
    }

    Scheduler::~Scheduler() {
    }

    void Scheduler::scheduleJob(Job* job) {
        m_jobList.push_back(job);
    }

    void Scheduler::cancelJob(Job* job) {
        std::list<Job*>::iterator i = std::find(m_jobList.begin(), m_jobList.end(), job);
        if (i != m_jobList.end()) {
            delete (*i);
            m_jobList.erase(i);
        }
    }

    void Scheduler::update(unsigned long int currentTime) {
        std::list<Job*>::iterator i = m_jobList.begin();
        while (i != m_jobList.end()) {
            switch ((*i)->scheduleType) {
                case ONCE:
                    if (currentTime > (*i)->argument) {
                        (*i)->execute();
                        delete (*i);
                        m_jobList.erase(i++);
                    } else
                        ++i;
                    break;
                case INTERVAL:
                    if (currentTime - (*i)->lastRun > (*i)->argument) {
                        (*i)->execute();
                        (*i)->lastRun = currentTime;
                    }
                    ++i;
                    break;
            }
        }



        for (std::list<Job*>::iterator i = m_jobList.begin(), e = m_jobList.end(); i != e; ++i) {
            switch ((*i)->scheduleType) {
                case ONCE:
                    if (currentTime > (*i)->argument) {

                    }
                    break;
                case INTERVAL:
                    break;
            }
        }
    }

}
