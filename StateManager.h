/* 
 * File:   StateManager.h
 * Author: chris
 *
 * Created on February 10, 2014, 10:13 PM
 */

#ifndef STATEMANAGER_H
#define	STATEMANAGER_H

#include "STATE/StateManager.h"

class StateManager : public STATE::StateManager {
public:
    StateManager();
    virtual ~StateManager();
    static StateManager& getInstance();
private:
    
};

#endif	/* STATEMANAGER_H */

