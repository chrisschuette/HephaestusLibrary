/* 
 * File:   Application.h
 * Author: chris
 *
 * Created on June 13, 2013, 3:17 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include "GL/GLApp.h"

namespace STATE {
    class StateManager;
}

class Application : public GL::GLApp {
public:
    Application();
    virtual void Init();
    virtual void Exec();
    virtual bool IsDone();
    virtual void Shutdown();
    virtual ~Application();
private:
    
};

#endif	/* APPLICATION_H */

