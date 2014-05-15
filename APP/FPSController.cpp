/* 
 * File:   FPSController.cpp
 * Author: chris
 * 
 * Created on March 12, 2014, 9:08 AM
 */

#include "FPSController.h"
#include "Clock.h"
#include <iostream>
#include <boost/thread/thread.hpp>

namespace APP {

    FPSController::FPSController(const Clock& clock)
    : LOG::Source("FPSController") 
    , m_FPSLimit(0)
    , m_msecPerFrame(-1)
    , m_waitTime(0)
    , m_frameCounter(0)
    , m_frames(200)
    , m_clock(clock)
    {
        //gettimeofday(&m_lastDraw, NULL);
        //gettimeofday(&m_lastCounterStart, NULL);
        m_lastDraw = m_clock.getTime();
        m_lastCounterStart = m_clock.getTime();
    }

    FPSController::FPSController(const Clock& clock, int FPS)
    : LOG::Source("FPSController") 
    , m_FPSLimit(FPS)
    , m_msecPerFrame(1 / (float) FPS * 1000)
    , m_waitTime(0)
    , m_frameCounter(0)
    , m_frames(200)
    , m_clock(clock) {
        //gettimeofday(&m_lastDraw, NULL);
        //gettimeofday(&m_lastCounterStart, NULL);
        m_lastDraw = m_clock.getTime();
        m_lastCounterStart = m_clock.getTime();
    }

    FPSController::~FPSController() {
    }

    void FPSController::limitFPS() {
        double elapsedTime;
        unsigned long int now;
        now = m_clock.getTime();

        elapsedTime = now - m_lastDraw;

        m_waitTime += m_msecPerFrame - elapsedTime;

        boost::this_thread::sleep(boost::posix_time::milliseconds(std::max(m_waitTime, 0.f)));
        m_lastDraw = now;

        m_frameCounter++;
        if (m_frameCounter >= m_frames) {
            double elapsed;
            elapsed = now - m_lastCounterStart;

            // determine FPS
            float FPS = (float) m_frames / elapsed * 1000.f;
            m_lastCounterStart = now;
            m_frameCounter = 0;
            L(normal) << "FPS: " << FPS;
        }

    }

}
