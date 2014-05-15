/* 
 * File:   ConsoleSink.h
 * Author: chris
 *
 * Created on June 17, 2013, 12:35 AM
 */

#ifndef CONSOLESINK_H
#define	CONSOLESINK_H

#include "Sink.h"

namespace LOG {
class ConsoleSink: public Sink {
public:
    ConsoleSink();
        virtual void processRecord(const Record& record);

    virtual ~ConsoleSink();
private:

};
}
#endif	/* CONSOLESINK_H */

