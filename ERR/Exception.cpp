/* 
 * File:   Exception.cpp
 * Author: chris
 * 
 * Created on June 12, 2013, 8:30 PM
 */

#include "Exception.h"
#include "../UTIL/string.h"

namespace ERR {

    Exception::Exception(std::string msg, const char* function, const char* file, int line) throw ()
    : m_msg(msg)
    , m_errorCode(0)
    , m_function(function)
    , m_file(file)
    , m_line(line) {
    }

    Exception::Exception(int errorCode, std::string msg, const char* function, const char* file, int line) throw ()
    : m_msg(msg)
    , m_errorCode(errorCode)
    , m_function(function)
    , m_file(file)
    , m_line(line)
    {
    }

    Exception::~Exception() throw () {
    }

    const char* Exception::what() const throw () {
        m_message = m_msg + " Exception thrown in function " + m_function + "(...) in file " + m_file + " at line " + UTIL::toString(m_line);
        return m_message.c_str();
    }
}