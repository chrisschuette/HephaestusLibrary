/* 
 * File:   FileSink.h
 * Author: chris
 *
 * Created on June 17, 2013, 12:45 AM
 */

#ifndef FILESINK_H
#define	FILESINK_H

#include "Sink.h"

#include <string>
#include <fstream>

namespace LOG {
class FileSink: public Sink {
public:
    FileSink(std::string filename);
            virtual void processRecord(const Record& record);

    virtual ~FileSink();
private:
    std::string m_filename;
    std::ofstream m_fileStream;
};
}
#endif	/* FILESINK_H */

