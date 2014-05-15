/* 
 * File:   State.h
 * Author: chris
 *
 * Created on June 13, 2013, 2:47 PM
 */

#ifndef STATE_H
#define	STATE_H

#include "../LOG/Source.h"
#include "Context.h"

#include <string>

namespace STATE {
    class Context;
class State: public LOG::Source {
public:
    State(std::string name, Context& context);
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void OnEnter() = 0;
    virtual void OnLeave() = 0;
    virtual void OnResize(int width, int height) = 0;
    virtual ~State();
    
    std::string getName() const { return m_name; }
private:
    std::string m_name;
};
}
#endif	/* STATE_H */

