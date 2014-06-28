/* 
 * File:   StateManager.h
 * Author: chris
 *
 * Created on June 13, 2013, 2:51 PM
 */

#ifndef STATE_STATEMANAGER_H
#define	STATE_STATEMANAGER_H

#include "Context.h"
#include <memory>
#include <map>
#include <string>

namespace STATE {
    class State;
    class Context;
    class ConstructionContext;
    
    class StateManager {
    public:
        typedef State * (*tCreator)(Context& context, ConstructionContext* constructionContext);
        typedef std::map<std::string, tCreator> tCreatorMap;
    public:
        StateManager();
        virtual ~StateManager();
        bool Register(std::string type, tCreator aCreator);
        bool IsDone() const { return m_Done; }
        std::string GetCurrentStateName();
        void scheduleTransitionToNewState(std::string nextState, ConstructionContext* constructionContext = 0);
        void scheduleShutdown();
        const std::string& getNextStateName() const { return m_nextState; }
        void Update(unsigned long int time, unsigned long int diff, Context& context);
        void Render(Context& context);
        State& getCurrentState();
    private:
        State * Create (std::string type, Context& context, ConstructionContext* constructionContext);
        void SetDone(bool done) { m_Done = done; }
        void SwitchToState( std::string type, Context& context, ConstructionContext* constructionContext);
        std::string m_nextState;
        ConstructionContext* m_nextConstructionContext;
        tCreatorMap m_creators;
        State* m_pCurrentState;
        bool m_Done;
        bool m_shutdown;
    };
}
#endif	/* STATE_STATEMANAGER_H */

