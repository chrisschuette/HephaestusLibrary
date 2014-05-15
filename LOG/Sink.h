/* 
 * File:   Sink.h
 * Author: chris
 *
 * Created on June 17, 2013, 12:32 AM
 */

#ifndef SINK_H
#define	SINK_H

namespace LOG {
    class Record;
class Sink {
public:
    Sink();
    virtual void processRecord(const Record& record) = 0;
    virtual ~Sink();
private:

};
}

#endif	/* SINK_H */

