/* 
 * File:   AutoTerminator.h
 * Author: chris
 *
 * Created on June 16, 2013, 10:44 PM
 */

#ifndef AUTOTERMINATOR_H
#define	AUTOTERMINATOR_H

#include <utility>

namespace LOG {
    class Core;
class AutoTerminator {
public:
    explicit AutoTerminator(Core& core) : m_core(core) {}
    virtual ~AutoTerminator();
    Core const & obj () const {return m_core;}
    Core & obj () {return m_core;}
private:
    Core& m_core;
};
template <typename T>
const AutoTerminator& operator<< (const AutoTerminator& ae, const T& arg)
{
    ae.obj() << arg;
    return ae;
}

}
#endif	/* AUTOTERMINATOR_H */

