/* 
 * File:   FPSController.h
 * Author: chris
 *
 * Created on March 12, 2014, 9:08 AM
 */

#ifndef FPSCONTROLLER_H
#define	FPSCONTROLLER_H

#include <time.h>
#include "../LOG/Source.h"

namespace APP {
    class Clock;
    class FPSController: public LOG::Source {
    public:
        FPSController(const Clock& clock);
        FPSController(const Clock& clock, int FPS);
        virtual ~FPSController();
        void limitFPS();
    private:
        int m_FPSLimit;
        float m_msecPerFrame;
        //timeval m_lastDraw;
        unsigned long int m_lastDraw;
        float m_waitTime;
        int m_frameCounter;
        //timeval m_lastCounterStart;
        unsigned long int m_lastCounterStart;
        int m_frames;
        const Clock& m_clock;
    };
}
#endif	/* FPSCONTROLLER_H */

