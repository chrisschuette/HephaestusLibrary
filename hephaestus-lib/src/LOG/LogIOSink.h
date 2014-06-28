/* 
 * File:   LogIOSink.h
 * Author: chris
 *
 * Created on June 17, 2013, 12:54 AM
 */

#ifndef LOGIOSINK_H
#define	LOGIOSINK_H

#include "Sink.h"
#include <boost/asio.hpp>
#include <boost/scoped_ptr.hpp>

namespace LOG {
class LogIOSink: public Sink {
public:
    LogIOSink(unsigned int port = 28777);
    virtual ~LogIOSink();
            virtual void processRecord(const Record& record);

private:
    boost::asio::io_service m_io_service;
    boost::scoped_ptr<boost::asio::ip::tcp::socket> m_socket;
    unsigned int m_port;
};
}
#endif	/* LOGIOSINK_H */

