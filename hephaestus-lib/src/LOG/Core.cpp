/* 
 * File:   Core.cpp
 * Author: chris
 * 
 * Created on June 16, 2013, 9:45 PM
 */

#include "Core.h"
#include <ctime>
#include <string.h>
#include <iomanip>

namespace LOG {
    std::auto_ptr<Core> Core::m_pInstance(0);
    Core::Core() {
    }

    Core::~Core() {
                for(std::list<Sink*>::const_iterator i = m_sinks.begin(), end = m_sinks.end(); i != end; ++i) {
                    Sink* sink = (*i);
                    if(sink)
                        delete sink;
                }

    }

    Core& Core::getInstance() {
        if(m_pInstance.get() ==0) {
            m_pInstance = std::auto_ptr<Core>(new Core);
        }
        return *m_pInstance;
    }
    
    void Core::addSink(Sink* sink) {
        m_sinks.push_back(sink);
    }


    Core& Core::startRecord(const char* file, int line, const char* function, std::string sender, SEVERITY severity) {
        m_mtxRecord.lock();
        m_record.setFile(file);
        m_record.setFunction(function);
        m_record.setSeverity(severity);
        m_record.setLine(line);
        m_record.setSender(sender);
        m_record.getStream().str("");
        return *this;
    }

    void Core::finishRecord() const {
/*        time_t rawtime;
        struct tm * timeinfo;
        char buffer [80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, "%I:%M:%S", timeinfo);
        m_logFile << std::setw(10) << buffer << " || "
                << std::setw(15) << m_record.getSender() << " || "
                << std::setw(15) << m_record.getFunction() << "(...) in "
                << std::setw(25) << m_record.getFile() << " at line " << std::setw(3) << m_record.getLine() << " || ";

        switch (m_record.getSeverity()) {
            case 0:
                m_logFile << std::setw(5) << "*";
                break;
            case 1:
                m_logFile << std::setw(5) << "**";
                break;
            case 2:
                m_logFile << std::setw(5) << "***";
                break;
            case 3:
                m_logFile << std::setw(5) << "****";
                break;
            case 4:
                m_logFile << std::setw(5) << "*****";
                break;
        }

        m_logFile << " --||-- "
                << m_record.getStream().str() << std::endl;
        
        */
        for(std::list<Sink*>::const_iterator i = m_sinks.begin(), end = m_sinks.end(); i != end; ++i)
            (*i)->processRecord(m_record);
        
        m_mtxRecord.unlock();
    }

    template <>
    const Core& operator<< <Terminator>(const Core& core, const Terminator& arg) {
        core.finishRecord();
        return core;
    }
}

