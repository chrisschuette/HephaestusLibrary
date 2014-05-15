/* 
 * File:   SoundFile.h
 * Author: chris
 *
 * Created on March 11, 2014, 2:44 PM
 */

#ifndef SOUNDFILE_H
#define	SOUNDFILE_H

#include "../LOG/Source.h"

namespace SND {

    class SoundFile: public LOG::Source {
    public:
        SoundFile(std::string name, unsigned char * rawData, unsigned int rawDataSize, bool ownsData);
        virtual ~SoundFile();

        // info functions
        unsigned int getNumChannels() const { return m_numChannels; }
        unsigned int getBitPerSample() const { return m_bitsPerSample; }
        int getFrequency() const { return m_frequency; }
        // io functions
        // return:
        // >=0, bytes read
        // <0, error
        virtual int read(unsigned char* buffer, unsigned int bytesToRead) = 0;
    protected:
        bool m_ownsData;
        unsigned char * m_rawData;
        unsigned int m_rawDataSize;
        int m_frequency;
        unsigned int m_numChannels;
        unsigned int m_bitsPerSample;
    };
}
#endif	/* SOUNDFILE_H */

