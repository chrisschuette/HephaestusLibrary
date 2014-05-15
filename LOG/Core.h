/* 
 * File:   Core.h
 * Author: chris
 *
 * Created on June 16, 2013, 9:45 PM
 */

#ifndef CORE_H
#define	CORE_H

#include <iostream>
#include "severity.h"
#include "Record.h"
#include "Sink.h"
#include "AutoTerminator.h"
#include <boost/thread/mutex.hpp>
#include <list>
#include <memory>

#define L(sev) LOG::AutoTerminator(LOG::Core::getInstance().startRecord(__FILE__,__LINE__,__FUNCTION__,getName(),sev))
#define L_SENDER(sev,sender) LOG::AutoTerminator(LOG::Core::getInstance().startRecord(__FILE__,__LINE__,__FUNCTION__,sender,sev))

namespace LOG {
    class Terminator;
    class Core {
    public:
        static Core& getInstance();
        void addSink(Sink* sink);
        Core& startRecord(const char* file, int line, const char* function, std::string sender, SEVERITY severity);
        void finishRecord() const;
    private:
        Core();
        virtual ~Core();
        template <typename T> 
        friend const Core& operator<<(const Core& core, const T& arg);
        mutable LOG::Record m_record;
        mutable boost::mutex m_mtxRecord;
        std::list<Sink*> m_sinks;
        
        static std::auto_ptr<Core> m_pInstance;
        friend class std::auto_ptr<Core>;
    };
    template <typename T>
    const Core& operator<<(const Core& core, const T& arg) {
        core.m_record.getStream() << arg;
        return core;
    }
}
#endif	/* CORE_H */

