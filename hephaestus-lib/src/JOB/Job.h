/* 
 * File:   Job.h
 * Author: chris
 *
 * Created on June 12, 2014, 9:44 AM
 */

#ifndef JOB_H
#define	JOB_H

namespace JOB {

    enum SCHEDULE_TYPE {
        ONCE, INTERVAL
    };

    struct Job {

        Job(SCHEDULE_TYPE type, unsigned long int argument)
        : scheduleType(type)
        , argument(argument)
        , lastRun(0) {

        }
        virtual void execute() = 0;
        SCHEDULE_TYPE scheduleType;
        unsigned long int argument;
        unsigned long int lastRun;
    };
}
#endif	/* JOB_H */

