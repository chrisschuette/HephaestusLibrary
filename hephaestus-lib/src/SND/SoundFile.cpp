/* 
 * File:   SoundFile.cpp
 * Author: chris
 * 
 * Created on March 11, 2014, 2:44 PM
 */

#include "SoundFile.h"
#include "../LOG/Core.h"

#define NAME "SoundFile"

namespace SND {

    SoundFile::SoundFile(std::string name, unsigned char * rawData, unsigned int rawDataSize, bool ownsData)
    : m_rawData(rawData)
    , m_rawDataSize(rawDataSize)
    , m_ownsData(ownsData) {
    }

    SoundFile::~SoundFile() {
        if (m_ownsData && m_rawData)
            delete [] m_rawData;
    }
}
