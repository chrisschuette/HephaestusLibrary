/* 
 * File:   Record.cpp
 * Author: chris
 * 
 * Created on June 16, 2013, 10:08 PM
 */

#include "Record.h"

namespace LOG {

    Record::Record()
    : m_severity(normal)
    , m_line(0) {
        time(&m_time);
    }

    Record::Record(std::string file, int line, std::string function, std::string sender, SEVERITY severity)
    : m_file(file)
    , m_line(line)
    , m_function(function)
    , m_sender(sender)
    , m_severity(severity) {
        time(&m_time);
    }

    Record::~Record() {
    }
}
