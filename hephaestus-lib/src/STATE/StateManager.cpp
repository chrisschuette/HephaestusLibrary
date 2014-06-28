/* 
 * File:   StateManager.cpp
 * Author: chris
 * 
 * Created on June 13, 2013, 2:51 PM
 */

#include "StateManager.h"
#include "../ERR/ERR.h"
#include "State.h"
#include "ConstructionContext.h"

#include "../LOG/Core.h"

#define NAME "StateManager"

namespace STATE {

    StateManager::StateManager()
    : m_pCurrentState(0)
    , m_Done(false)
    , m_shutdown(false)
    , m_nextConstructionContext(0) {
        L(normal) << "StateManager created.";
    }

    StateManager::~StateManager() {
        if (m_pCurrentState) {
            m_pCurrentState->OnLeave();
            delete m_pCurrentState;
            m_pCurrentState = 0;
        }
        if(m_nextConstructionContext)
            delete m_nextConstructionContext;
    }

    bool StateManager::Register(std::string type, tCreator aCreator) {
        L(normal) << type << " registered.";

        return m_creators.insert(tCreatorMap::value_type((type), (aCreator))).second;
    }

    State * StateManager::Create(std::string type, Context& context, ConstructionContext* constructionContext) {
        tCreatorMap::iterator i = m_creators.find(type);
        if (i != m_creators.end()) {
            tCreator aCreator = (*i).second;
            L(normal) << type << " created.";
            return aCreator(context, constructionContext);
        } else {
            L(error) << "Unknow State " << type;
            THROWS("State creation failed.");
        }
        return 0;
    }

    void StateManager::SwitchToState(std::string type, Context& context, ConstructionContext* constructionContext) {
        L(normal) << "Switching to state " << type << "...";
        if (m_pCurrentState != 0) {
            m_pCurrentState->OnLeave();
        }
        delete m_pCurrentState;
        m_nextState.clear();
        m_pCurrentState = 0;
        m_pCurrentState = Create(type, context, constructionContext);
        m_pCurrentState->OnEnter();
    }

    std::string StateManager::GetCurrentStateName() {
        std::string name;
        if (m_pCurrentState)
            name = m_pCurrentState->getName();
        return name;
    }

    void StateManager::scheduleTransitionToNewState(std::string nextState, ConstructionContext* constructionContext) {
        m_nextState = nextState;
        m_nextConstructionContext = constructionContext;
    }

    void StateManager::scheduleShutdown() {
        m_shutdown = true;
    }

    void StateManager::Update(unsigned long int time, unsigned long int diff, Context& context) {
        if (m_shutdown) {
            if (m_pCurrentState != 0) {
                m_pCurrentState->OnLeave();
            }
            delete m_pCurrentState;
            m_nextState.clear();
            if(m_nextConstructionContext) {
                delete m_nextConstructionContext;
                m_nextConstructionContext = 0;
            }
            m_pCurrentState = 0;
            m_Done = true;
            return;
        }

        if (m_nextState.size() != 0) {
            SwitchToState(m_nextState, context, m_nextConstructionContext);
            if(m_nextConstructionContext) {
                delete m_nextConstructionContext;
                m_nextConstructionContext = 0;
            }
        }

        if (m_pCurrentState)
            m_pCurrentState->Update(time, diff);
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
