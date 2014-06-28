/* 
 * File:   Exception.h
 * Author: chris
 *
 * Created on June 12, 2013, 8:30 PM
 */

#ifndef EXCEPTION_H
#define	EXCEPTION_H

#include <exception>
#include <string>

namespace ERR {
class Exception : public std::exception {
public:
    Exception(std::string msg, const char* function, const char* file, int line) throw ();
    Exception(int errorCode, std::string msg, const char* function, const char* file, int line) throw ();
    virtual ~Exception() throw ();
    virtual const char* what() const throw ();
private:
    std::string m_function;
    std::string m_file;
    int m_line;
    std::string m_msg;
    int m_errorCode;
    mutable std::string m_message;
};
}
#endif	/* EXCEPTION_H */

