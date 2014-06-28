/* 
 * File:   FileSink.cpp
 * Author: chris
 * 
 * Created on June 17, 2013, 12:45 AM
 */

#include "FileSink.h"
#include "Record.h"
#include "../ERR/ERR.h"
#include <iomanip>

namespace LOG {
FileSink::FileSink(std::string filename)
: Sink()
, m_filename(filename)
{
    m_fileStream.open(filename.c_str());
    if(!m_fileStream.is_open())
        THROWS("Unable to open file " + filename);
}

FileSink::~FileSink() {
    if(m_fileStream.is_open())
        m_fileStream.close();
}

void FileSink::processRecord(const Record& record) {
       time_t rawtime = record.getTime();
        struct tm * timeinfo;
        char buffer [80];

        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, "%I:%M:%S", timeinfo);
        m_fileStream << std::setw(10) << buffer << " || "
                << std::setw(25) << record.getSender() << " || "
                << std::setw(25) << record.getFunction() << "(...) in "
                << std::setw(35) << record.getFile() << " at line " << std::setw(3) << record.getLine() << " || ";

        switch (record.getSeverity()) {
            case 0:
                m_fileStream << std::setw(5) << "*";
                break;
            case 1:
                m_fileStream << std::setw(5) << "**";
                break;
            case 2:
                m_fileStream << std::setw(5) << "***";
                break;
            case 3:
                m_fileStream << std::setw(5) << "****";
                break;
            case 4:
                m_fileStream << std::setw(5) << "*****";
                break;
        }

        m_fileStream << " --||-- "
                << record.getStream().str() << std::endl;
}

}
