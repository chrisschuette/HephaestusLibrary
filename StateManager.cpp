/* 
 * File:   StateManager.cpp
 * Author: chris
 * 
 * Created on February 10, 2014, 10:13 PM
 */

#include "StateManager.h"

StateManager::StateManager() : STATE::StateManager() {
}

StateManager::~StateManager() {
}

StateManager& StateManager::getInstance() {
    static StateManager stateManager;
    return stateManager;
}