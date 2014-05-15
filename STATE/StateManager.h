/* 
 * File:   StateManager.h
 * Author: chris
 *
 * Created on June 13, 2013, 2:51 PM
 */

#ifndef STATE_STATEMANAGER_H
#define	STATE_STATEMANAGER_H

#include "../LOG/Source.h"
#include <memory>
#include <map>
#include <string>

namespace STATE {
    class State;
    class Context;

    class StateManager : public LOG::Source {
    public:
        typedef State * (*tCreator)(Context& context);
        typedef std::map<std::string, tCreator> tCreatorMap;
    public:
        StateManager();
        virtual ~StateManager();
        bool Register(std::string type, tCreator aCreator);
        State * Create (std::string type, Context& context);
        void SwitchToState( std::string type, Context& context );
        void SetDone(bool done) { m_Done = done; }
        bool IsDone() const { return m_Done; }
        std::string GetCurrentStateName();
        void scheduleTransitionToNewState(std::string nextState);
        void scheduleShutdown();
        const std::string& getNextStateName() const { return m_nextState; }
        void Update(Context& context);
        void Render(Context& context);
        State& getCurrentState();
    private:
        std::string m_nextState;
        tCreatorMap m_creators;
        State* m_pCurrentState;
        bool m_Done;
        bool m_shutdown;
    };
}
#endif	/* STATE_STATEMANAGER_H */

