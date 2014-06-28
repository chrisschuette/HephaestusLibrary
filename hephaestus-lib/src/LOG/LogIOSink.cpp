/* 
 * File:   LogIOSink.cpp
 * Author: chris
 * 
 * Created on June 17, 2013, 12:54 AM
 */

#include "LogIOSink.h"
#include "Record.h"
#include "../ERR/ERR.h"
#include <boost/array.hpp>
#include "../UTIL/string.h"
#include <iomanip>
#include "../LOG/Core.h"

#define NAME "LogIOSink"

namespace LOG {
    using boost::asio::ip::tcp;

    LogIOSink::LogIOSink(unsigned int port) : Sink(), m_port(port), m_socket(new tcp::socket(m_io_service)) {
        try {
            tcp::resolver resolver(m_io_service);
            tcp::resolver::query query("localhost", UTIL::toString(m_port));
            tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

            boost::asio::connect(*m_socket, endpoint_iterator);
        } catch (boost::system::system_error& e) {
            L(error) << "Unable to connect to Log.IO server at localhost:" << m_port;
            //THROWS("Initialisation of Log.IO sink failed.");
        }
    }

    LogIOSink::~LogIOSink() {
    }

    void LogIOSink::processRecord(const Record& record) {
        try {

            boost::asio::streambuf request;
            std::ostream request_stream(&request);
            request_stream << "+log|";
            request_stream << record.getSender();
            request_stream << "|";
            request_stream << record.getFunction();
            request_stream << "|info|";
            time_t rawtime = record.getTime();
            struct tm * timeinfo;
            char buffer [80];

            timeinfo = localtime(&rawtime);

            strftime(buffer, 80, "%I:%M:%S", timeinfo);
            request_stream << std::setw(10) << buffer << " || "
                    << std::setw(25) << record.getFile() << " at line " << std::setw(3) << record.getLine() << " || ";

            switch (record.getSeverity()) {
                case 0:
                    request_stream << std::setw(5) << "*";
                    break;
                case 1:
                    request_stream << std::setw(5) << "**";
                    break;
                case 2:
                    request_stream << std::setw(5) << "***";
                    break;
                case 3:
                    request_stream << std::setw(5) << "****";
                    break;
                case 4:
                    request_stream << std::setw(5) << "*****";
                    break;
            }

            request_stream << " --||-- "
                    << record.getStream().str() << std::endl;

            request_stream << "\r\n";
/* DEBUG
            boost::asio::streambuf::const_buffers_type bufs = request.data();
            std::string str(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + request.size());
            std::cout << str;
        */    
            // Send the request.
            boost::asio::write(*m_socket, request);

        } catch (boost::system::system_error& e) {
            //L(error) << "Unable to connect to Log.IO server.";
            //THROWS("Initialisation of Log.IO sink failed.");
        }
    }

}
