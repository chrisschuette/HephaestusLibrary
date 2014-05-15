/* 
 * File:   ConsoleSink.cpp
 * Author: chris
 * 
 * Created on June 17, 2013, 12:35 AM
 */

#include "ConsoleSink.h"
#include "Record.h"

#include <iostream>
#include <iomanip>

namespace LOG {
ConsoleSink::ConsoleSink() : Sink() {
}

ConsoleSink::~ConsoleSink() {
}

void ConsoleSink::processRecord(const Record& record)  {
           time_t rawtime = record.getTime();
        struct tm * timeinfo;
        char buffer [80];

        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, "%I:%M:%S", timeinfo);
        std::cout << std::setw(10) << buffer << " || "
                << std::setw(25) << record.getSender() << " || "
                << std::setw(25) << record.getFunction() << "(...) in "
                << std::setw(35) << record.getFile() << " at line " << std::setw(3) << record.getLine() << " || ";

        switch (record.getSeverity()) {
            case 0:
                std::cout << std::setw(5) << "*";
                break;
            case 1:
                std::cout << std::setw(5) << "**";
                break;
            case 2:
                std::cout << std::setw(5) << "***";
                break;
            case 3:
                std::cout << std::setw(5) << "****";
                break;
            case 4:
                std::cout << std::setw(5) << "*****";
                break;
        }

        std::cout << " --||-- "
                << record.getStream().str() << std::endl;
}

}
