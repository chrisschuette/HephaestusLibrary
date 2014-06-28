/* 
 * File:   WaveFile.cpp
 * Author: chris
 * 
 * Created on March 11, 2014, 3:15 PM
 */

#include "WaveFile.h"
#include "../../LOG/Core.h"

#define NAME "WaveFile"

namespace SND {
    namespace Formats {

        WaveFile::WaveFile(unsigned char * rawData, unsigned int rawDataSize, bool ownsData)
        : SND::SoundFile("WaveFile", rawData, rawDataSize, ownsData)
        , m_waveData(0)
        , m_waveDataSize(0)
        {
            processHeader();
        }

        WaveFile::~WaveFile() {
        }

        void WaveFile::processHeader() {
            byte* ptr = m_rawData;

            RIFF_Header* riffHeader;
            riffHeader = (RIFF_Header*) ptr;
            // L(normal) << std::string((char*) riffHeader->chunkID, 4);
            // L(normal) << std::string((char*) riffHeader->format, 4);

            ptr += sizeof ( RIFF_Header);

            WAVE_Format* waveFormat;
            waveFormat = (WAVE_Format*) ptr;
            // L(normal) << std::string((char*) waveFormat->subChunkID, 4);

            //check for extra parameters;
            if (waveFormat->subChunkSize > 16) {
                 L(normal) << "Extra parameter found.";
                ptr += sizeof (word);
            }

            ptr += sizeof ( WAVE_Format);

            WAVE_Data* waveData;
            waveData = (WAVE_Data*) ptr;

            ptr += sizeof ( WAVE_Data);
            m_waveData = ptr;
            m_waveDataPtr = m_waveData;

            // L(normal) << std::string((char*) waveData->subChunkID, 4);

            //Now we set the variables that we passed in with the
            //data from the structs
            m_waveDataSize = waveData->subChunk2Size;
            m_frequency = waveFormat->sampleRate;

            m_numChannels = waveFormat->numChannels;
            m_bitsPerSample = waveFormat->bitsPerSample;
        }

        int WaveFile::getWaveDataSize() const {
            return m_waveDataSize;
        }

        int WaveFile::read(unsigned char* buffer, unsigned int bytesToRead) {
            long int toCopy = bytesToRead;
            toCopy = std::min(toCopy, m_waveDataSize - (m_waveDataPtr - m_waveData));
            std::memcpy(buffer, m_waveDataPtr, toCopy);
            m_waveDataPtr += toCopy;
            return toCopy;
        }

    }
}
