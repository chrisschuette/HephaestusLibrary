/* 
 * File:   StateManager.cpp
 * Author: chris
 * 
 * Created on June 13, 2013, 2:51 PM
 */

#include "StateManager.h"
#include "../ERR/ERR.h"
#include "State.h"

namespace STATE {

    StateManager::StateManager()
    : LOG::Source("StateManager")
    , m_pCurrentState(0)
    , m_Done(false)
    , m_shutdown(false) {
        L(normal) << "StateManager created.";
    }

    StateManager::~StateManager() {
        if (m_pCurrentState) {
            m_pCurrentState->OnLeave();
            delete m_pCurrentState;
            m_pCurrentState = 0;
        }
        L(normal) << "StateManager destroyed.";
    }

    bool StateManager::Register(std::string type, tCreator aCreator) {
        L(normal) << type << " registered.";

        return m_creators.insert(tCreatorMap::value_type((type), (aCreator))).second;
    }

    State * StateManager::Create(std::string type, Context& context) {
        tCreatorMap::iterator i = m_creators.find(type);
        if (i != m_creators.end()) {
            tCreator aCreator = (*i).second;
            L(normal) << type << " created.";
            return aCreator(context);
        } else {
            L(error) << "Unknow State " << type;
            THROWS("State creation failed.");
        }
        return 0;
    }

    void StateManager::SwitchToState(std::string type, Context& context) {
        if (m_pCurrentState != 0) {
            m_pCurrentState->OnLeave();
        }
        delete m_pCurrentState;
        m_nextState.clear();
        m_pCurrentState = 0;
        m_pCurrentState = Create(type, context);
        m_pCurrentState->OnEnter();
    }

    std::string StateManager::GetCurrentStateName() {
        std::string name;
        if (m_pCurrentState)
            name = m_pCurrentState->getName();
        return name;
    }

    void StateManager::scheduleTransitionToNewState(std::string nextState) {
        m_nextState = nextState;
    }

    void StateManager::scheduleShutdown() {
        m_shutdown = true;
    }

    void StateManager::Update(Context& context) {
        if (m_shutdown) {
            if (m_pCurrentState != 0) {
                m_pCurrentState->OnLeave();
            }
            delete m_pCurrentState;
            m_nextState.clear();
            m_pCurrentState = 0;
            m_Done = true;
            return;
        }

        if (m_nextState.size() != 0)
            SwitchToState(m_nextState, context);

        if (m_pCurrentState)
            m_pCurrentState->Update();
    }

    void StateManager::Render(Context& context) {
        if (m_pCurrentState)
            m_pCurrentState->Render();
    }

    State& StateManager::getCurrentState() {
        if (!m_pCurrentState)
            THROWS("Current state not defined.");
        return *m_pCurrentState;
    }
}
