/* 
 * File:   Record.h
 * Author: chris
 *
 * Created on June 16, 2013, 10:08 PM
 */

#ifndef RECORD_H
#define	RECORD_H

#include <string>
#include <sstream>
#include "severity.h"

namespace LOG {
class Record {
public:
    Record();
    Record(std::string file, int line, std::string function, std::string sender, SEVERITY severity);
    void setFunction(std::string function) { m_function = function; }
    void setFile(std::string file) { m_file = file; }
    void setSeverity(SEVERITY severity) { m_severity = severity; }
    void setSender(std::string sender) { m_sender = sender; }
    void setLine(int line) { m_line = line; }
    
    const std::string& getFunction() const { return m_function; }
    const std::string& getFile() const { return m_file; }
    int getLine() const { return m_line; }
    const std::string& getSender() const { return m_sender; }
    SEVERITY getSeverity() const { return m_severity; }
    time_t getTime() const { return m_time; }
    
    const std::stringstream& getStream() const { return m_message; }
    std::stringstream& getStream() { return m_message; }
    virtual ~Record();
private:
    std::string m_file;
    int m_line;
    std::string m_function;
    std::string m_sender;
    SEVERITY m_severity;
    std::stringstream m_message;
    time_t m_time;
};
}
#endif	/* RECORD_H */

